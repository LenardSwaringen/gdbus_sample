#include <glib.h>
#include "helloWorld.h"

int main(int argc, char *argv[])
{
    GError *error = NULL;
    /// 创建代理对象，与服务端建立连接
    ExampleTest* proxy = example_test_proxy_new_for_bus_sync(
                                                G_BUS_TYPE_SESSION,       ///< 总线类型 session/system
                                                G_DBUS_PROXY_FLAGS_NONE,  ///< 代理标志
                                                "com.example",            ///< 需要连接的服务端名称
                                                "/com/example/helloWorld",///< 需要连接的服务端的对象路径
                                                NULL, &error);

    if (proxy == NULL)
    {
        g_print("error: %s\n", error->message);
        return -1;
    }

    /// 调用服务端接口
    gchar *response = NULL;
    gboolean result = example_test_call_hello_world_sync(proxy,          ///< 代理对象
                                                         "client",       ///< 传递给服务端的参数
                                                         &response,      ///< 服务端接口输出的参数
                                                         NULL, &error);

    if (!result)
    {
        g_print("invoke remote method failed: %s\n", error->message);
        return -1;
    }

    g_print("received: %s\n", response);

    g_object_unref(proxy);
    return 0;
}
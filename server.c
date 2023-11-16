#include <glib.h>
#include "helloWorld.h"

static gboolean on_handle_hello_world (ExampleTest *interface, GDBusMethodInvocation *invocation, const gchar *greeting, gpointer user_data)
{
    gchar* response = g_strdup_printf ("Hello world %s !", greeting);
    example_test_complete_hello_world(interface, invocation, response);
    g_print("response: %s\n", response);
    g_free(response);
    return TRUE;
}

static void on_name_acquired(GDBusConnection *connection, const gchar *name, gpointer user_data)
{
    /// 创建服务端对象
    ExampleTest* interface = example_test_skeleton_new();
    /// 注册服务端回调函数，当服务端helloWorld接口被调用时，将调用on_handle_hello_world函数
    g_signal_connect (interface, "handle-hello-world", G_CALLBACK(on_handle_hello_world), NULL);
    GError *error = NULL;
    g_dbus_interface_skeleton_export (G_DBUS_INTERFACE_SKELETON (interface), connection, "/com/example/helloWorld", &error);
}

int main(int argc, char *argv[])
{

    GMainLoop* loop = g_main_loop_new (NULL, FALSE);

    /// 注册服务端名称
    g_bus_own_name(G_BUS_TYPE_SESSION,
                   "com.example",                   ///< 服务端名称
                   G_BUS_NAME_OWNER_FLAGS_NONE,     ///< 服务端行为标志
                   NULL,                            ///< 服务端成功注册到D-BUS总线时的回调函数
                   on_name_acquired,                ///< 服务端成功声明服务名时将被调用
                   NULL,NULL,NULL);

    g_main_loop_run (loop);

    return 0;
}

























//#include "helloWorld.h"
//
//
//
//static void on_name_acquired  (GDBusConnection *connection,
//                             const gchar     *name,
//                             gpointer         user_data)
//{

//    g_dbus_interface_skeleton_export (G_DBUS_INTERFACE_SKELETON (hello_world_skeleton_new ()),
//                                      connection,
//                                      "/com/example/HelloWorld",
//                                      NULL);
//}
//
//static const GDBusInterfaceVTable interface_vtable =
//        {
//                on_handle_hello_world ,
//                NULL,
//                NULL,
//        };
//
//int main (int argc, char *argv[])
//{
//    guint owner_id;
//    GMainLoop *loop = g_main_loop_new(NULL, FALSE);;
//    owner_id = g_bus_own_name (G_BUS_TYPE_SESSION,
//                               "com.example.HelloWorld",
//                               G_BUS_NAME_OWNER_FLAGS_NONE,
//                               on_handle_hello_world ,
//                               NULL,
//                               NULL,
//                               NULL,
//                               NULL);
//
//
//    /* Run the loop */
//    g_main_loop_run (loop);
//
//    g_bus_unown_name (owner_id);
//
//    return 0;
//}
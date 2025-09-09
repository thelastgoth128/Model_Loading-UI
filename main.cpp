#include <gtk/gtk.h>
#include "model_loader.hpp"
#include "renderer.cpp"

// Async callback for file selection
static void on_file_dialog_response(GtkFileDialog *dialog, GAsyncResult *res, gpointer user_data) {
    GFile *file = gtk_file_dialog_open_finish(dialog, res, NULL);
    if (file) {
        const char *path = g_file_peek_path(file); 
        if (path) {
            g_print("Selected file: %s\n", path);
            
            g_print("Calling renderer...\n");
            launch_glfw_renderer();
            g_print("Renderer call finished.\n");
        }
        // TODO: Pass 'path' to your model loading logic
        g_object_unref(file);
    }
}

// Trigger file dialog with filters
static void open_file(GtkWidget *widget, gpointer data) {
    GtkFileDialog *dialog = gtk_file_dialog_new();

    // Create filter for model file types
    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "3D Model Files");
    gtk_file_filter_add_suffix(filter, "obj");
    gtk_file_filter_add_suffix(filter, "fbx");
    gtk_file_filter_add_suffix(filter, "glb");

    // Wrap filter in GListModel
    GListStore *store = g_list_store_new(GTK_TYPE_FILE_FILTER);
    g_list_store_append(store, filter);
    gtk_file_dialog_set_filters(dialog, G_LIST_MODEL(store));

    // Show dialog asynchronously
    gtk_file_dialog_open(dialog,
                         GTK_WINDOW(gtk_widget_get_root(widget)),
                         NULL,
                         (GAsyncReadyCallback)on_file_dialog_response,
                         NULL);
}

// Basic GTK app window
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Model Loader");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);


}

int main (int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("ModelLoader", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);

    return status;
}
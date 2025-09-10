#include <gtk/gtk.h>
#include "model.h"
#include "renderer.cpp"

// Async callback for file selection
Model* ourModel = nullptr;

static void on_file_dialog_response(GtkFileDialog *dialog, GAsyncResult *res, gpointer user_data) {
    GFile *file = gtk_file_dialog_open_finish(dialog, res, NULL);
    if (file) {
        const char *path = g_file_peek_path(file); 
        if (path) {
            g_print("Selected file: %s\n", path);

            // Delete previous model if it exists
            if (ourModel) {
                delete ourModel;
                ourModel = nullptr;
                g_print("Previous model deleted.\n");
            }

            // Normalize path (optional)
            std::string fixedPath = std::string(path);
            std::replace(fixedPath.begin(), fixedPath.end(), '\\', '/');

            // Launch renderer
            g_print("Calling renderer...\n");
            launch_glfw_renderer(fixedPath.c_str());
            g_print("Renderer call finished.\n");
        }
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
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);

    // Create overlay container
    GtkWidget *overlay = gtk_overlay_new();
    gtk_window_set_child(GTK_WINDOW(window), overlay);

    // Background image
    GtkWidget *background = gtk_picture_new_for_filename("C:/Users/HP/OneDrive/Documentos/Cyrus/Projects/model_loading_UI/tree.jpg");
    gtk_widget_set_hexpand(background, TRUE);
    gtk_widget_set_vexpand(background, TRUE);
    gtk_overlay_set_child(GTK_OVERLAY(overlay), background);

    // Centered label
    GtkWidget *label = gtk_label_new("🧊 Load 3D Model");
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(label, GTK_ALIGN_CENTER);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), label);
    gtk_widget_add_css_class(label, "title");

    // Bottom-right Browse button
    GtkWidget *buttonBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign(buttonBox, GTK_ALIGN_END);
    gtk_widget_set_valign(buttonBox, GTK_ALIGN_END);

    GtkWidget *browseButton = gtk_button_new_with_label("Browse");
    g_signal_connect(browseButton, "clicked", G_CALLBACK(open_file), NULL);
    gtk_box_append(GTK_BOX(buttonBox), browseButton);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), buttonBox);

    // Optional: Spinner (bottom-left or center)
    // GtkWidget *spinner = gtk_spinner_new();
    // gtk_spinner_start(GTK_SPINNER(spinner));
    // gtk_widget_set_halign(spinner, GTK_ALIGN_START);
    // gtk_widget_set_valign(spinner, GTK_ALIGN_END);
    // gtk_overlay_add_overlay(GTK_OVERLAY(overlay), spinner);

    // Load CSS
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "C:/Users/HP/OneDrive/Documentos/Cyrus/Projects/model_loading_UI/style.css");
    gtk_style_context_add_provider_for_display(gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("com.example.ModelLoader", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    

    return status;
}

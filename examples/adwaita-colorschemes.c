#include <gtk/gtk.h>

typedef struct
{
  const char *name;
  const char *window_bg;
  const char *window_fg;
  const char *view_bg;
  const char *view_fg;
  const char *accent_bg;
  const char *accent_fg;
  const char *headerbar_bg;
  const char *headerbar_fg;
  const char *card_bg;
  const char *card_fg;
  const char *success;
  const char *warning;
  const char *error;
  const char *link;
} Scheme;

static const Scheme schemes[] = {
  {
    "Adwaita Blue (default)",
    "#fafafa", "#202020", "#ffffff", "#202020",
    "#3584e4", "#ffffff", "#f6f5f4", "#202020",
    "#ffffff", "#202020", "#2ec27e", "#f5c211", "#e01b24", "#1c71d8"
  },
  {
    "Dracula",
    "#282a36", "#f8f8f2", "#21222c", "#f8f8f2",
    "#bd93f9", "#282a36", "#44475a", "#f8f8f2",
    "#44475a", "#f8f8f2", "#50fa7b", "#f1fa8c", "#ff5555", "#8be9fd"
  },
  {
    "Nord",
    "#2e3440", "#eceff4", "#3b4252", "#e5e9f0",
    "#88c0d0", "#2e3440", "#434c5e", "#eceff4",
    "#434c5e", "#eceff4", "#a3be8c", "#ebcb8b", "#bf616a", "#81a1c1"
  },
  {
    "Gruvbox Dark",
    "#282828", "#ebdbb2", "#32302f", "#ebdbb2",
    "#d79921", "#282828", "#3c3836", "#ebdbb2",
    "#3c3836", "#ebdbb2", "#98971a", "#d79921", "#cc241d", "#458588"
  },
  {
    "Catppuccin Mocha",
    "#1e1e2e", "#cdd6f4", "#181825", "#cdd6f4",
    "#89b4fa", "#1e1e2e", "#313244", "#cdd6f4",
    "#313244", "#cdd6f4", "#a6e3a1", "#f9e2af", "#f38ba8", "#74c7ec"
  },
};

static char *
build_css (const Scheme *scheme)
{
  return g_strdup_printf (
    "* {"
    "  -gtk-icon-palette: error %s, warning %s, success %s;"
    "}"
    "@define-color window_bg_color %s;"
    "@define-color window_fg_color %s;"
    "@define-color view_bg_color %s;"
    "@define-color view_fg_color %s;"
    "@define-color accent_bg_color %s;"
    "@define-color accent_fg_color %s;"
    "@define-color headerbar_bg_color %s;"
    "@define-color headerbar_fg_color %s;"
    "@define-color popover_bg_color %s;"
    "@define-color popover_fg_color %s;"
    "@define-color card_bg_color %s;"
    "@define-color card_fg_color %s;"
    "@define-color dialog_bg_color %s;"
    "@define-color dialog_fg_color %s;"
    "@define-color sidebar_bg_color %s;"
    "@define-color sidebar_fg_color %s;"
    "@define-color success_bg_color %s;"
    "@define-color success_fg_color %s;"
    "@define-color warning_bg_color %s;"
    "@define-color warning_fg_color %s;"
    "@define-color error_bg_color %s;"
    "@define-color error_fg_color %s;"
    "@define-color link_color %s;"
    "@define-color border_color alpha(%s, 0.28);"
    "@define-color shade_color alpha(black, 0.36);"
    "@define-color scrollbar_outline_color alpha(%s, 0.5);",
    scheme->error, scheme->warning, scheme->success,
    scheme->window_bg,
    scheme->window_fg,
    scheme->view_bg,
    scheme->view_fg,
    scheme->accent_bg,
    scheme->accent_fg,
    scheme->headerbar_bg,
    scheme->headerbar_fg,
    scheme->view_bg,
    scheme->view_fg,
    scheme->card_bg,
    scheme->card_fg,
    scheme->window_bg,
    scheme->window_fg,
    scheme->headerbar_bg,
    scheme->headerbar_fg,
    scheme->success,
    scheme->window_bg,
    scheme->warning,
    scheme->window_bg,
    scheme->error,
    scheme->window_bg,
    scheme->link,
    scheme->window_fg,
    scheme->window_fg);
}

static void
apply_scheme (GtkCssProvider *provider,
              guint           index)
{
  char *css;

  if (index >= G_N_ELEMENTS (schemes))
    index = 0;

  css = build_css (&schemes[index]);
  gtk_css_provider_load_from_string (provider, css);
  g_free (css);
}

static void
selection_changed (GtkDropDown   *dropdown,
                   GParamSpec    *pspec,
                   GtkCssProvider *provider)
{
  apply_scheme (provider, gtk_drop_down_get_selected (dropdown));
}

static GtkWidget *
create_preview (void)
{
  GtkWidget *box;
  GtkWidget *title;
  GtkWidget *entry;
  GtkWidget *switcher;
  GtkWidget *progress;
  GtkWidget *button_box;
  GtkWidget *button;
  GtkWidget *suggested;
  GtkWidget *destructive;

  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 12);
  gtk_widget_add_css_class (box, "card");
  gtk_widget_set_margin_top (box, 12);
  gtk_widget_set_margin_bottom (box, 12);
  gtk_widget_set_margin_start (box, 12);
  gtk_widget_set_margin_end (box, 12);

  title = gtk_label_new ("Preview widgets");
  gtk_widget_add_css_class (title, "title-3");
  gtk_box_append (GTK_BOX (box), title);

  entry = gtk_entry_new ();
  gtk_editable_set_text (GTK_EDITABLE (entry), "Search colors");
  gtk_box_append (GTK_BOX (box), entry);

  switcher = gtk_switch_new ();
  gtk_switch_set_active (GTK_SWITCH (switcher), TRUE);
  gtk_box_append (GTK_BOX (box), switcher);

  progress = gtk_progress_bar_new ();
  gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progress), 0.64);
  gtk_box_append (GTK_BOX (box), progress);

  button_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 6);
  button = gtk_button_new_with_label ("Default");
  gtk_box_append (GTK_BOX (button_box), button);

  suggested = gtk_button_new_with_label ("Suggested");
  gtk_widget_add_css_class (suggested, "suggested-action");
  gtk_box_append (GTK_BOX (button_box), suggested);

  destructive = gtk_button_new_with_label ("Destructive");
  gtk_widget_add_css_class (destructive, "destructive-action");
  gtk_box_append (GTK_BOX (button_box), destructive);

  gtk_box_append (GTK_BOX (box), button_box);

  return box;
}

static void
activate (GtkApplication *app)
{
  GtkWidget *window;
  GtkWidget *root;
  GtkWidget *label;
  GtkWidget *dropdown;
  GtkStringList *list;
  GtkCssProvider *provider;
  guint i;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Adwaita Colorscheme Switcher");
  gtk_window_set_default_size (GTK_WINDOW (window), 440, 320);

  provider = gtk_css_provider_new ();
  gtk_style_context_add_provider_for_display (gtk_widget_get_display (window),
                                              GTK_STYLE_PROVIDER (provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  root = gtk_box_new (GTK_ORIENTATION_VERTICAL, 12);
  gtk_widget_set_margin_top (root, 12);
  gtk_widget_set_margin_bottom (root, 12);
  gtk_widget_set_margin_start (root, 12);
  gtk_widget_set_margin_end (root, 12);
  gtk_window_set_child (GTK_WINDOW (window), root);

  label = gtk_label_new ("Pick a popular colorscheme");
  gtk_widget_add_css_class (label, "title-4");
  gtk_box_append (GTK_BOX (root), label);

  list = gtk_string_list_new (NULL);
  for (i = 0; i < G_N_ELEMENTS (schemes); i++)
    gtk_string_list_append (list, schemes[i].name);

  dropdown = gtk_drop_down_new (G_LIST_MODEL (list), NULL);
  gtk_drop_down_set_selected (GTK_DROP_DOWN (dropdown), 0);
  gtk_box_append (GTK_BOX (root), dropdown);
  g_object_unref (list);

  gtk_box_append (GTK_BOX (root), create_preview ());

  g_signal_connect (dropdown, "notify::selected", G_CALLBACK (selection_changed), provider);

  apply_scheme (provider, 0);
  g_object_set_data_full (G_OBJECT (window), "app-css-provider", provider, g_object_unref);

  gtk_window_present (GTK_WINDOW (window));
}

int
main (int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.Example.AdwaitaColorSchemes", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

# Adwaita Nova Installation

1. Copy this folder into your themes directory:
   - User-only: `~/.themes/Adwaita-Nova`
   - System-wide: `/usr/share/themes/Adwaita-Nova`
2. Apply it:
   - GNOME Tweaks -> Appearance -> Legacy Applications -> **Adwaita Nova**
   - or CLI: `gsettings set org.gnome.desktop.interface gtk-theme 'Adwaita-Nova'`

This package includes both `gtk-3.0` and `gtk-4.0` CSS files.


Optional: create your own archive locally (not tracked in git):
`tar -czf Adwaita-Nova.tar.gz Adwaita-Nova`

Important: keep the included `gtk-3.0/assets` and `gtk-4.0/assets` folders next to the CSS files; they provide checkbox/radio symbolic assets.

Entry CSS files now use Adwaita-style `gtk-contained*.css` imports for compatibility.

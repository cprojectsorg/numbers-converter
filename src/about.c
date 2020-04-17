/*
	Numbers Converter.
	Copyright (C) 2020  Hasan Alsamra hasan@cprojects.org

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <gtk/gtk.h>

void showAbout() {
	GtkWidget *dialog = gtk_about_dialog_new();
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("./numbers-converter.ico", NULL);
	
	char license[] = "\n\t\t\tCopyright (C) 2020  Cprojects info@cprojects.org\n\n\t"
	"This program is free software: you can redistribute it and/or modify\n\t"
	"it under the terms of the GNU General Public License as published by\n\t"
	"the Free Software Foundation, either version 3 of the License, or (at\n\t"
	"your option) any later version.\n\n\t"
	"This program is distributed in the hope that it will be useful,\n\t"
	"but WITHOUT ANY WARRANTY; without even the implied warranty of\n\t"
	"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n\t"
	"See the GNU General Public License for more details.\n\n\t"
	"You should have received a copy of the GNU General Public License\n\t"
	"along with this program.  If not, see <https://www.gnu.org/licenses/>\n\t";
	
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), "Numbers Converter");
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "1.0");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),"Copyright © 2020 Cprojects.");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "A simple numbers converter program.");
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), "http://www.cprojects.org/");
	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
	gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(dialog), license);
	
	g_object_unref(pixbuf), pixbuf = NULL;
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

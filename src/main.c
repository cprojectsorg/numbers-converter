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
#include <stdbool.h>
#include <ctype.h>
#include "converter.h"
#include "main.h"
#include "about.h"

static void activate();
void fillContents();
void buttonsCallBack(GtkButton*, GtkEntry*);
void updateValues(GtkEntry*);
void validateField(GtkEntry*, gpointer);

int main(int argc, char *argv[]) {
	int status;
	app = gtk_application_new("org.cprojects.numbersconverter", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	
	return status;
}

static void activate() {
	window = gtk_application_window_new(app);
	
	GError *error = NULL;
	GtkIconTheme *icon_theme;
	GdkPixbuf *pixbuf;

	icon_theme = gtk_icon_theme_get_default();
	pixbuf = gtk_icon_theme_load_icon(icon_theme, "numbers-converter", 128, 0, &error);
	
	if(!pixbuf) {
		g_warning("Couldn’t load icon: %s", error->message);
		g_error_free(error);
	} else
		g_object_unref(pixbuf);
	
	gtk_window_set_icon_name(GTK_WINDOW(window), "numbers-converter");
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	gtk_window_set_title(GTK_WINDOW(window), "Numbers Converter");
	gtk_window_set_default_size(GTK_WINDOW(window), 400, -1);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), false);
	
	fillContents();
	
	gtk_widget_show_all(window);
}

void fillContents() {
	decimalField = gtk_entry_new();
	hexaField = gtk_entry_new();
	binaryField = gtk_entry_new();
	octalField = gtk_entry_new();
	
	gtk_entry_set_max_length(GTK_ENTRY(decimalField), 14);
	gtk_entry_set_max_length(GTK_ENTRY(hexaField), 12);
	gtk_entry_set_max_length(GTK_ENTRY(binaryField), 47);
	gtk_entry_set_max_length(GTK_ENTRY(octalField), 16);
	
	GtkWidget *menuBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	GtkWidget *mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	GtkWidget *contentBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	
	GtkStyleContext *context;
	context = gtk_widget_get_style_context(contentBox);
	gtk_style_context_add_class(context, "contentBox");
	
	GtkWidget *fieldsGrid = gtk_grid_new();
	GtkWidget *menuBar = gtk_menu_bar_new();
	GtkWidget *hlpParent = gtk_menu_new();
	
	GtkWidget *helpMenu = gtk_menu_item_new_with_label("Help");
	GtkWidget *aboutItem = gtk_menu_item_new_with_label("About");
	
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(helpMenu), hlpParent);
	gtk_menu_shell_append(GTK_MENU_SHELL(hlpParent), aboutItem);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), helpMenu);
	
	gtk_box_pack_start(GTK_BOX(menuBox), menuBar, false, false, 0);
	gtk_box_pack_start(GTK_BOX(mainBox), menuBox, false, false, 0);
	
	clearButton = gtk_button_new_with_label("Clear");
	quitButton = gtk_button_new_with_label("Quit");
	
	copyDecimalButton = gtk_button_new_with_label("Copy");
	copyHexaButton = gtk_button_new_with_label("Copy");
	copyBinaryButton = gtk_button_new_with_label("Copy");
	copyOctalButton = gtk_button_new_with_label("Copy");
	
	gtk_widget_set_hexpand(decimalField, true);
	gtk_widget_set_vexpand(decimalField, true);
	
	gtk_container_add(GTK_CONTAINER(window), mainBox);
	gtk_container_set_border_width(GTK_CONTAINER(window), 0);
	
	gtk_box_pack_start(GTK_BOX(mainBox), contentBox, false, false, 0);
	gtk_box_pack_start(GTK_BOX(contentBox), fieldsGrid, false, false, 0);
	
	gtk_grid_set_column_spacing(GTK_GRID(fieldsGrid), 9);
	gtk_grid_set_row_spacing(GTK_GRID(fieldsGrid), 9);
	
	gtk_grid_attach(GTK_GRID(fieldsGrid), gtk_label_new("Decimal:"), 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(fieldsGrid), decimalField, 1, 0, 2, 1);
	gtk_grid_attach(GTK_GRID(fieldsGrid), copyDecimalButton, 3, 0, 1, 1);
	
	gtk_grid_attach(GTK_GRID(fieldsGrid), gtk_label_new("Hexadecimal:"), 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(fieldsGrid), hexaField, 1, 1, 2, 1);
	gtk_grid_attach(GTK_GRID(fieldsGrid), copyHexaButton, 3, 1, 1, 1);
	
	gtk_grid_attach(GTK_GRID(fieldsGrid), gtk_label_new("Binary:"), 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(fieldsGrid), binaryField, 1, 2, 2, 1);
	gtk_grid_attach(GTK_GRID(fieldsGrid), copyBinaryButton, 3, 2, 1, 1);
	
	gtk_grid_attach(GTK_GRID(fieldsGrid), gtk_label_new("Octal:"), 0, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(fieldsGrid), octalField, 1, 3, 2, 1);
	gtk_grid_attach(GTK_GRID(fieldsGrid), copyOctalButton, 3, 3, 1, 1);
	
	gtk_grid_attach(GTK_GRID(fieldsGrid), clearButton, 0, 4, 2, 1);
	gtk_grid_attach(GTK_GRID(fieldsGrid), quitButton, 2, 4, 2, 1);
	
	g_signal_connect_swapped(quitButton, "clicked", G_CALLBACK(gtk_widget_destroy), window);
	
	g_signal_connect(decimalField, "changed", G_CALLBACK(validateField), NULL);
	g_signal_connect(hexaField, "changed", G_CALLBACK(validateField), NULL);
	g_signal_connect(binaryField, "changed", G_CALLBACK(validateField), NULL);
	g_signal_connect(octalField, "changed", G_CALLBACK(validateField), NULL);
	
	g_signal_connect(decimalField, "key-release-event", G_CALLBACK(updateValues), NULL);
	g_signal_connect(hexaField, "key-release-event", G_CALLBACK(updateValues), NULL);
	g_signal_connect(binaryField, "key-release-event", G_CALLBACK(updateValues), NULL);
	g_signal_connect(octalField, "key-release-event", G_CALLBACK(updateValues), NULL);
	
	g_signal_connect(clearButton, "clicked", G_CALLBACK(buttonsCallBack), NULL);
	g_signal_connect(copyDecimalButton, "clicked", G_CALLBACK(buttonsCallBack), decimalField);
	g_signal_connect(copyHexaButton, "clicked", G_CALLBACK(buttonsCallBack), hexaField);
	g_signal_connect(copyBinaryButton, "clicked", G_CALLBACK(buttonsCallBack), binaryField);
	g_signal_connect(copyOctalButton, "clicked", G_CALLBACK(buttonsCallBack), octalField);
	
	g_signal_connect(G_OBJECT(aboutItem), "activate", G_CALLBACK(showAbout), NULL);
	
	GtkCssProvider *provider = gtk_css_provider_new();
	GdkDisplay *display = gdk_display_get_default();
	GdkScreen *screen = gdk_display_get_default_screen(display);
	gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	gtk_css_provider_load_from_data(provider, "*{font-size: 13px;} .contentBox{padding: 3px 9px 9px 9px;}", -1, NULL);
}

void buttonsCallBack(GtkButton *button, GtkEntry *field) {
	if(GTK_BUTTON(clearButton) == button) {
		gtk_entry_set_text(GTK_ENTRY(decimalField), "");
		gtk_entry_set_text(GTK_ENTRY(hexaField), "");
		gtk_entry_set_text(GTK_ENTRY(binaryField), "");
		gtk_entry_set_text(GTK_ENTRY(octalField), "");
	} else
		gtk_clipboard_set_text(gtk_clipboard_get(GDK_SELECTION_CLIPBOARD), gtk_entry_get_text(field), -1);
}

void updateValues(GtkEntry *field) {
	if(GTK_ENTRY(decimalField) == field) {
		gtk_entry_set_text(GTK_ENTRY(hexaField), convertTo(gtk_entry_get_text(field), 10, 16));
		gtk_entry_set_text(GTK_ENTRY(binaryField), convertTo(gtk_entry_get_text(field), 10, 2));
		gtk_entry_set_text(GTK_ENTRY(octalField), convertTo(gtk_entry_get_text(field), 10, 8));
	} else if(GTK_ENTRY(hexaField) == field) {
		gtk_entry_set_text(GTK_ENTRY(decimalField), convertTo(gtk_entry_get_text(field), 16, 10));
		gtk_entry_set_text(GTK_ENTRY(binaryField), convertTo(gtk_entry_get_text(field), 16, 2));
		gtk_entry_set_text(GTK_ENTRY(octalField), convertTo(gtk_entry_get_text(field), 16, 8));
	} else if(GTK_ENTRY(binaryField) == field) {
		gtk_entry_set_text(GTK_ENTRY(decimalField), convertTo(gtk_entry_get_text(field), 2, 10));
		gtk_entry_set_text(GTK_ENTRY(hexaField), convertTo(gtk_entry_get_text(field), 2, 16));
		gtk_entry_set_text(GTK_ENTRY(octalField), convertTo(gtk_entry_get_text(field), 2, 8));
	} else if(GTK_ENTRY(octalField) == field) {
		gtk_entry_set_text(GTK_ENTRY(decimalField), convertTo(gtk_entry_get_text(field), 8, 10));
		gtk_entry_set_text(GTK_ENTRY(hexaField), convertTo(gtk_entry_get_text(field), 8, 16));
		gtk_entry_set_text(GTK_ENTRY(binaryField), convertTo(gtk_entry_get_text(field), 8, 2));
	}
}

void validateField(GtkEntry *entry, gpointer data) {
	GtkEditable *editable = GTK_EDITABLE(entry);
	int i, count = 0, length = strlen(gtk_entry_get_text(entry));
	char entryData[length];
	strcpy(entryData, gtk_entry_get_text(entry));
	static char result[200];
	memset(result, 0, 200);
	
	if(GTK_ENTRY(decimalField) == entry) {
		for(i=0; i < length; i++) {
			if(isdigit(entryData[i]))
				result[count++] = entryData[i];
			else if(entryData[i] == '-' && count == 0)
				result[count++] = entryData[i];
		}
	} else if(GTK_ENTRY(hexaField) == entry) {
		for(i=0; i < length; i++) {
			if(isdigit(entryData[i]))
				result[count++] = entryData[i];
			else if(isalpha(entryData[i]) && getHexValue(entryData[i]) != 0)
				result[count++] = toupper(entryData[i]);
			else if(entryData[i] == '-' && count == 0)
				result[count++] = entryData[i];
		}
	} else if(GTK_ENTRY(binaryField) == entry) {
		for(i=0; i < length; i++) {
			if(isdigit(entryData[i]) && entryData[i] < '2')
				result[count++] = entryData[i];
			else if(entryData[i] == '-' && count == 0)
				result[count++] = entryData[i];
		}
	} else if(GTK_ENTRY(octalField) == entry) {
		for(i=0; i < length; i++) {
			if(isdigit(entryData[i]) && entryData[i] < '8')
				result[count++] = entryData[i];
			else if(entryData[i] == '-' && count == 0)
				result[count++] = entryData[i];
		}
	}
	
	g_signal_handlers_block_by_func(G_OBJECT(editable), G_CALLBACK(validateField), data);
	gtk_entry_set_text(entry, result);
	g_signal_handlers_unblock_by_func(G_OBJECT(editable), G_CALLBACK(validateField), data);
	
	g_signal_stop_emission_by_name(G_OBJECT(editable), "changed");
}

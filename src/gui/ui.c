#include "ui.h"

#include <gdk-pixbuf/gdk-pixbuf.h>

typedef struct Entries
{

}

typedef struct UserInterface
{
	GtkWindow *window;
	GtkImage *image;
	GtkWidget *loadImgButton;
	
	GtkImage *resPlateImg;

	GtkButton *detectButton;
	GtkButton *playVideoButton;

	GtkLabel *plateLabel;

	SDL_Surface *imageToProcess;
	SDL_Surface *resultImage;

	gchar *sourceImgPath;
	gchar *currentImgPath;

	gchar *videoPath;

}UserInterface;

/*----------------event handlers---------------*/

void Display(GtkImage *image, gchar *path)
{
	gtk_image_set_from_file(image, path);
}

/*2 usage : choose video or image*/
void on_file_choose(GtkButton *button, gpointer user_data)
{
	UserInterface *ui = user_data;
	gchar *filePath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button));


	if (g_str_has_suffix(filePath, ".mp4") == TRUE) // user loaded video file (restrict to .mp4)
	{
		g_print("on_load_video()\n");
		ui -> videoPath = filePath;

		ui -> currentImgPath = NULL;

		Display(ui -> image, "vid_icon.png");
	}
	
	else // loaded image file (any type supported)
	{
		ui -> videoPath = NULL;
		ui -> currentImgPath = filePath;

		SDL_Surface *img = load_image(ui -> currentImgPath);
		ui -> sourceImgPath = ui -> currentImgPath;
		ui -> imageToProcess = img;
	
		/*Resize image if necessary*/
		if (img -> h > 600 || img -> w > 600)
		{
			SDL_SaveBMP(ResizeToFit(img, 600, 600), "scaled.bmp");
			ui -> currentImgPath = "scaled.bmp";
		}

		Display(ui -> image, ui -> currentImgPath);
		g_print("on_load_image()\n");
	}
}

void on_detect(GtkButton *button, gpointer user_data)
{
	UserInterface *ui = user_data;

	if (!ui -> sourceImgPath)
		return;

	/*Detect Plate*/
	gchar *plate = GetPlateFromImage(ui -> sourceImgPath, 3);

	/*Save the result image*/
	ui -> resultImage = ResizeToFit(load_image("final.bmp"), 600, 600);
	SDL_SaveBMP(ui -> resultImage, "final_resized.bmp");

	/*Set the text on the plate label*/
	gtk_label_set_text(ui -> plateLabel, plate);


	SDL_SaveBMP(BuildImageRes(plate), "test_build_plate.bmp");


	/*Display the images*/
	Display(ui -> resPlateImg, "test_build_plate.bmp");
	Display(ui -> image, "final_resized.bmp");
}

void on_play_video(GtkButton *button, gpointer user_data)
{
	UserInterface *ui = user_data;

	if (ui -> videoPath)
		PlayVid(ui -> videoPath);
}

/*---------------------------------------------*/

int main()
{
	init_sdl();
	gtk_init(NULL, NULL);
	GtkBuilder *builder = gtk_builder_new();
	GError *error = NULL;

	if (gtk_builder_add_from_file(builder, "ui.glade", &error) == 0)
	{
		g_printerr("Error loading file :%s\n", error -> message);
		g_clear_error(&error);
		return 1;
	}
	gtk_builder_connect_signals(builder, NULL);


	GtkWindow *window = GTK_WINDOW(gtk_builder_get_object(builder, "main_window"));
        GtkImage *image = GTK_IMAGE(gtk_builder_get_object(builder, "image"));
	GtkWidget *loadImgButton = GTK_WIDGET(gtk_builder_get_object(builder, "load_image_button"));
	GtkButton *detectButton = GTK_BUTTON(gtk_builder_get_object(builder, "detect_button"));
	GtkButton *playVideoButton = GTK_BUTTON(gtk_builder_get_object(builder, "play_video_button"));
	GtkLabel *plateLabel = GTK_LABEL(gtk_builder_get_object(builder, "plate_label"));
	GtkImage *resPlateImg = GTK_IMAGE(gtk_builder_get_object(builder, "build_plate_image"));


	UserInterface ui = 
	{
		.window = window,
		.image = image,
		.loadImgButton = loadImgButton,
		.detectButton = detectButton,
		.plateLabel = plateLabel,
		.resPlateImg = resPlateImg,
		.playVideoButton = playVideoButton,
	};


	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(loadImgButton, "file-set", G_CALLBACK(on_file_choose), &ui);
	g_signal_connect(detectButton, "clicked", G_CALLBACK(on_detect), &ui);
	g_signal_connect(playVideoButton, "clicked", G_CALLBACK(on_play_video), &ui);

	gtk_main();

	return 0;
}

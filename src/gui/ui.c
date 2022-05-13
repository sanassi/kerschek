#include "ui.h"
#include <dirent.h>

#include <gdk-pixbuf/gdk-pixbuf.h>

typedef struct Entries
{
	GtkEntry *imgAngleEntry;
	GtkEntry *minSizeEntry;
	GtkEntry *imgMin_h_entry;
	GtkEntry *imgMax_h_entry;
	GtkEntry *imgMin_w_entry;
	GtkEntry *imgMax_w_entry;

	const gchar *imgAngle_str;
	const gchar *minSize_str;
	const gchar *imgMinH_str;
	const gchar *imgMaxH_str;
	const gchar *imgMinW_str;
	const gchar *imgMaxW_str;

	int imgAngle;
        int minSize;
        int imgMinH;
        int imgMaxH;
        int imgMinW;
        int imgMaxW;

}Entries;

typedef struct UserInterface
{
	GtkWindow *window;
	GtkImage *image;
	GtkWidget *loadImgButton;

	int maxImgHeight, maxImgWidth;
	
	GtkImage *resPlateImg;

	GtkButton *detectButton;
	GtkButton *playVideoButton;
	GtkButton *processVideoButton;
	GtkButton *nextButton;
        GtkButton *prevButton;
	GtkButton *playResultVidButton;
	int currentFrameNb;
	int nbFrames;

	GtkLabel *plateLabel;

	SDL_Surface *imageToProcess;
	SDL_Surface *resultImage;

	gchar *sourceImgPath;
	gchar *currentImgPath;

	gchar *videoPath;

	/*struct to store entry slots text*/
	Entries entries;

	/*arguments for img plate detection*/
	PlateDetectionArgs args;

}UserInterface;

/*----------------functions---------------*/

void GetEntriesText(Entries *e)
{
	e -> imgAngle_str = gtk_entry_get_text(e -> imgAngleEntry);
	e -> minSize_str = gtk_entry_get_text(e -> minSizeEntry);
	e -> imgMinH_str = gtk_entry_get_text(e -> imgMin_h_entry);
	e -> imgMaxH_str = gtk_entry_get_text(e -> imgMax_h_entry);
	e -> imgMinW_str = gtk_entry_get_text(e -> imgMin_w_entry);
        e -> imgMaxW_str = gtk_entry_get_text(e -> imgMax_w_entry);

	e -> imgAngle = strtoul(e -> imgAngle_str, NULL, 10);
        e ->  minSize = strtoul(e -> minSize_str, NULL, 10);
        e ->  imgMinH = strtoul(e -> imgMinH_str, NULL, 10);
        e ->  imgMaxH = strtoul(e -> imgMaxH_str, NULL, 10);
        e ->  imgMinW = strtoul(e -> imgMinW_str, NULL, 10);
        e ->  imgMaxW = strtoul(e -> imgMaxW_str, NULL, 10);
}

/*int max_h = img -> h / 2, min_h = 30;
        int max_w = img -> w / 3, min_w = 10;
        int min_size = 10;
        float max_ratio = 1, min_ratio = 0.2;
 */

void SetDetectionArgs(UserInterface *ui)
{
	PlateDetectionArgs *args = &ui -> args;
	Entries *e = &(ui -> entries);


	args -> angle = 3;
	args -> max_h = ui -> imageToProcess -> h / 2;
	args -> min_h = 30;
	args -> max_w = ui -> imageToProcess -> w / 3;
	args -> min_w = 10;
	args -> min_size = 10;
	args -> max_ratio = 1;
	args -> min_ratio = 0.2;

	/*
	if (*(e -> imgAngle_str) == '\0')
	{
		g_print("%s\n", e -> imgAngle_str);
		args -> angle = e -> imgAngle;
	}
        if (*(e -> minSize_str) != '\0')
		args -> min_size = e -> minSize;
	if (*(e -> imgMinH_str) != '\0')
                args -> min_h = e -> imgMinH;
	if (*(e -> imgMaxH_str) != '\0')
                args -> max_h = e -> imgMaxH;
	if (*(e -> imgMinW_str) != '\0')
                args -> min_w = e -> imgMinW;
	if (*(e -> imgMaxW_str) != '\0')
                args -> max_w = e -> imgMaxW;
	*/
}

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
	
		/*Resize image if necessary, save then set as current image*/
		if (img -> h > ui -> maxImgHeight || img -> w > ui -> maxImgWidth)
		{
			SDL_SaveBMP(ResizeToFit(img, ui -> maxImgHeight, ui -> maxImgWidth), "scaled.bmp");
			ui -> currentImgPath = "scaled.bmp";
		}

		/*display current image*/
		Display(ui -> image, ui -> currentImgPath);
		g_print("on_load_image()\n");
	}
}

void on_detect(GtkButton *button, gpointer user_data)
{
	UserInterface *ui = user_data;

	GetEntriesText(&(ui -> entries));
	SetDetectionArgs(ui);

	g_print("%i\n", (int) ui -> entries.imgAngle);

	if (!ui -> sourceImgPath)
		return;

	/*Detect Plate*/
	gchar *plate = GetPlateFromImage(ui -> sourceImgPath, &(ui -> args));

	/*Save the result image*/
	ui -> resultImage = ResizeToFit(load_image("final.bmp"), ui -> maxImgHeight, ui -> maxImgWidth);
	SDL_SaveBMP(ui -> resultImage, "final_resized.bmp");

	/*Set the text on the plate label*/
	gtk_label_set_text(ui -> plateLabel, plate);


	SDL_SaveBMP(BuildImageRes(plate), "test_build_plate.bmp");


	/*Display the images*/
	Display(ui -> resPlateImg, "test_build_plate.bmp");
	Display(ui -> image, "final_resized.bmp");
}

int GetNbFileInFolder(char *folder)
{
	int file_count = 0;
	DIR * dirp;
	struct dirent * entry;

	dirp = opendir(folder); /* There should be error handling after this */
	while ((entry = readdir(dirp)) != NULL) 
	{
    		if (entry->d_type == DT_REG) 
		{ /* If the entry is a regular file */
        	 	file_count++;
		}
	}
	closedir(dirp);

	return file_count;
}

void on_play_video(GtkButton *button, gpointer user_data)
{
	UserInterface *ui = user_data;

	if (ui -> videoPath)
		PlayVid(ui -> videoPath);

}

void on_process_video(GtkButton *button, gpointer user_data)
{
	UserInterface *ui = user_data;
	if (ui -> videoPath)
	{
		Display(ui -> image, "video_process_icon_3.png");
		g_print("\nmade it here\n");
		ReadVideo(ui -> videoPath);

        	ui -> nbFrames = GetNbFileInFolder("frames");
	}
}

void on_prev_clicked(GtkButton *button, gpointer user_data)
{
	UserInterface *ui = user_data;

	if (ui -> videoPath)
	{
		ui -> currentFrameNb -= 1;
		if (ui -> currentFrameNb < 0)
		{
			ui -> currentFrameNb = ui -> nbFrames - 1;
		}

		char *res_path;
		int err = asprintf(&res_path, "%s%i%s", "frames/", ui -> currentFrameNb, ".bmp");
		g_print("%s\n", res_path);
		Display(ui -> image, res_path);
	}
}

void on_next_clicked(GtkButton *button, gpointer user_data)
{
	UserInterface *ui = user_data;

	if (ui -> videoPath)
        {
		ui -> currentFrameNb += 1;
		if (ui -> currentFrameNb >= ui -> nbFrames)
		{
			ui -> currentFrameNb = 0;
		}
		char *res_path;
                int err = asprintf(&res_path, "%s%i%s", "frames/", ui -> currentFrameNb, ".bmp");
		g_print("%s\n", res_path);
		Display(ui -> image, res_path);
        }
}

void on_play_result_video(GtkButton *button, gpointer user_data)
{
	UserInterface *ui = user_data;

	/*if user loaded a video*/
        if (ui -> videoPath)
        {
		/*check if output video file exists*/
		if (access("output.mp4", F_OK) == 0) 
		{
			PlayVid("output.mp4");
		}
        }
}

/*---------------------------------------------*/

int LaunchInterface()
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

	GtkButton *processVideoButton = GTK_BUTTON(gtk_builder_get_object(builder, "process_video_button"));
	GtkButton *nextButton = GTK_BUTTON(gtk_builder_get_object(builder, "next_button"));
	GtkButton *prevButton = GTK_BUTTON(gtk_builder_get_object(builder, "prev_button"));
	GtkButton *playResultVidButton = GTK_BUTTON(gtk_builder_get_object(builder, "play_result_video_button"));

	GtkEntry *imgAngleEntry = GTK_ENTRY(gtk_builder_get_object(builder, "img_angle_entry"));
        GtkEntry *minSizeEntry = GTK_ENTRY(gtk_builder_get_object(builder, "img_size_entry"));
        GtkEntry *imgMin_h_entry = GTK_ENTRY(gtk_builder_get_object(builder, "img_min_h_entry"));
        GtkEntry *imgMax_h_entry = GTK_ENTRY(gtk_builder_get_object(builder, "img_max_h_entry"));
        GtkEntry *imgMin_w_entry = GTK_ENTRY(gtk_builder_get_object(builder, "img_min_w_entry"));
        GtkEntry *imgMax_w_entry = GTK_ENTRY(gtk_builder_get_object(builder, "img_max_w_entry"));
	

        UserInterface ui =
        {
                .window = window,
                .image = image,
                .loadImgButton = loadImgButton,
                .detectButton = detectButton,
                .plateLabel = plateLabel,
                .resPlateImg = resPlateImg,

                .playVideoButton = playVideoButton,
		.processVideoButton = processVideoButton,
		.prevButton = prevButton,
		.nextButton = nextButton,
		.playResultVidButton = playResultVidButton,
		.currentFrameNb = 0,

		.maxImgHeight = 600,
		.maxImgWidth = 600,

		.entries = 
		{
			.imgAngleEntry = imgAngleEntry,
			.minSizeEntry = minSizeEntry,
			.imgMin_h_entry = imgMin_h_entry,
			.imgMax_h_entry = imgMax_h_entry,
			.imgMin_w_entry = imgMin_w_entry,
			.imgMax_w_entry = imgMax_w_entry,
		},

		.args = 
		{
			.angle = 0,
			.max_h = 0,
        		.min_h = 0,
        		.max_w = 0,
        		.min_w = 0,
        		.max_ratio = 0,
        		.min_ratio = 0,
		},
        };


        g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
        g_signal_connect(loadImgButton, "file-set", G_CALLBACK(on_file_choose), &ui);
        g_signal_connect(detectButton, "clicked", G_CALLBACK(on_detect), &ui);
        g_signal_connect(playVideoButton, "clicked", G_CALLBACK(on_play_video), &ui);
	g_signal_connect(processVideoButton, "clicked", G_CALLBACK(on_process_video), &ui);
	g_signal_connect(nextButton, "clicked", G_CALLBACK(on_next_clicked), &ui);
	g_signal_connect(prevButton, "clicked", G_CALLBACK(on_prev_clicked), &ui);
       	g_signal_connect(playResultVidButton, "clicked", G_CALLBACK(on_play_result_video), &ui);

	gtk_main();

	return 0;
}
int main()
{
	int err = LaunchInterface();

	return err;
}

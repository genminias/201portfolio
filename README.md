# 201 Portfolio

HELLO :) welcome to my IMDB movie database project.

Tutorial video: https://youtu.be/IX3wbcz7SQ8

WHAT THIS IS:
- This program reads in the movies from the basic IMDB dataset. You are then allowed to create or use an existing catalog to add movies to, delete movies from, and update movies in your catalog. These catalogs are also saved for future reference, so that you can still access them after you have restarted the program.

WHAT TO DOWNLOAD:
1) My repository, which includes this README.md file, portfolio.c, functions.c, functions.h, and a makefile.
2) The basics IMDB dataset - title.basics.tsv.gz. Make sure to only download that file. The file can be found here: https://datasets.imdbws.com/

HOW TO START:
1) Make sure both the repository and the dataset are unzipped and that all files are stored in the same folder.
2) Make your way to the folder through your terminal.
3) Run the command 'make portfolio'.
4) Run the command './portfolio'.
5) It should start!

HOW TO USE:
1) After the program reads in the dataset, you will be prompted to enter a username. You can choose to either create a new username or enter an existing one if you have used this program before. This username will be the name of your catalog, and if you want to create or use another catalog you must enter a new/different username. This username must also fit filename parameters, so you cannot create a username that will not create a file on your computer. If you try to do so, you will be prompted to re-enter a different username.
2) After entering a username, the main menu will appear. You can choose between editing the contents of your catalog (which will lead to the catalog menu), overwriting the catalog (which will delete all movies stored inside it), deleting the catalog (which will prompt you to enter a new/different username), changing users (which will also prompt you to enter a new/different username), and exiting the program.
3) If you choose to edit the catalog, the catalog menu will appear. From here you can choose between listing (printing) all of the movies in your catalog, adding a movie to your catalog, deleting a movie from your catalog, updating a movie in your catalog, going back to the main menu, or exiting the program.

KEY NOTES:
- When adding a movie, you are able to search by keyword(s). You do not need to include starting articles 'the', 'a', or 'an' if you do not want to, and your keyword(s) will search for movies that START with the keyword(s). You can also search for a movie using it's full title.
- You are not be able to add movies that do not exist in the IMDB movie dataset.
- When adding or updating a movie, you will be prompted to change the media type of the movie and the date the movie was added to your catalog. You must enter a valid date or the program will prompt you to re-enter one.
- Some years, runtime minutes, and genres in the IMDB dataset show up as '/N' for some movies. This means that the year, runtime minutes, or genres are unknown for a corresponding movie.

Have fun! If you are still confused about some things, try watching the video tutorial. The link is shown above.

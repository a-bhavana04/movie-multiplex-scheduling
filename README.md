## Movie Multiplex Scheduling

The Movie Multiplex Scheduler is a tool coded in C programming language to generate a weekly schedule for a given multiplex such that the profit for 
the multiplex is maximized.

The initial input parameters involve the number of screens in the multiplex that uses the Scheduler and its capacity. Following this, the number of 
movies to be screened for that week is taken as input.

For each movie,the release date,movie rating and language is taken from the users to calculate the demand and popularity scores of the movies respectively.

The movies are sorted based on the above-mentioned parameters. Screens are allotted per movie based on the combined demand and popularity score. 
Calculations are made to generate an occupancy matrix with the percentage of audience predicted to fill the capacity in that particular slot in a 
given screen and a binary matrix is generated to indicate whether the movie is being assigned to that slot or not. 
The schedule for a week is generated and crowd management is incorporated by adding appropriate time gaps for each consecutive slot and screen. 

The generated schedule for a week is stored in a file "movie_schedule.txt" which is opened in append mode each time the program is run.

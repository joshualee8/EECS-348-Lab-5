#include <stdio.h>

int main() {
    // declare variable to store user input (the desired score)
    int score;

    // declare and initialize array of possible scores 
    const int scores[] = {8, 7, 6, 3, 2};

    // declare and initialize array of names for each score 
    const char* scoreNames[] = {"TD + 2pt", "TD + FG", "TD", "3pt FG", "Safety"}; 

    // loop until user enters 0 or 1 to exit
    while (1) {
        // prompt user to enter score and give instructions to exit
        printf("Enter 0 or 1 to STOP\n");
        printf("Enter the NFL score: ");

        // read user input into score variable
        scanf("%d", &score);

        // exit loop if user enters 0 or 1
        if (score <= 1) {
            break;
        }

        // print header for possible combinations of scoring plays
        printf("possible combinations of scoring plays:\n");

        // loop through all possible combinations of scoring plays and print those that result in the desired score
        for (int td2 = 0; td2 * scores[0] <= score; td2++) { // iterate over the number of times a team could score a touchdown and convert it to a two-point conversion
            for (int td1 = 0; td1 * scores[1] <= score; td1++) { // iterate over the number of times a team could score a touchdown and convert it to a field goal 
                for (int td0 = 0; td0 * scores[2] <= score; td0++) { // iterate over the number of times a team could score a touchdown
                    for (int fg = 0; fg * scores[3] <= score; fg++) { // iterate over the number of times a team could score a field goal
                        for (int safety = 0; safety * scores[4] <= score; safety++) { // iterate over the number of times a team could score a safety
                            // calculate total score for current combination of scoring plays
                            int totalScore = td2 * scores[0] + td1 * scores[1] + td0 * scores[2] + fg * scores[3] + safety * scores[4];

                            // print current combination of scoring plays if it results in the desired score
                            if (totalScore == score) {
                                printf("%d %s, %d %s, %d %s, %d %s, %d %s\n", td2, scoreNames[0], td1, scoreNames[1], td0, scoreNames[2], fg, scoreNames[3], safety, scoreNames[4]);
                            }
                        }
                    }
                }
            }
        }
    }

    return 0; // return 0 to indicate successful termination
}
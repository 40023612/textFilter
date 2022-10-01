// Word Filter 1.0 
// create by Michael Pound 40023612

#include <string> // to use strings
#include <iostream> // using strams in and out ( for example cout and cin)
#include <fstream> // file streams
#include <vector> // to allow the use of vectors
#include <algorithm> // to allow me to transform string to lowercase

int IsCorrect()
{
    int usersSelection; // to check if banned words are correct
    std::cout << "Is the above correct? If so press 1 to carry on if no press any key to exit and\n make corrections to banned word text file." << std::endl;
    std::cin >> usersSelection;
    if (usersSelection == 1)
    {
        return(0);
    }
    else
    {
        exit(0);
    }
}

 std::string PickYourFile() // user options for what messages to filter
{
    std::cout << "**************Weclome to the sterling word filter*************" << std::endl;
    std::cout << "The word filter has 4 text files, just simply copy and paste in\nYour message and add to your banned worlds file to start filtering away" << std::endl;
    std::cout << "Please secoted which file to up load enter 1 = text1\nEnter 2 = text2\nEnter 3 = text3\nEnter 4= text4\n Enter 0 = End program" << std::endl;
    int userChoiceOfTextFile;
    std::cin >> userChoiceOfTextFile;
    std::string textFile;

    switch (userChoiceOfTextFile)
    {
    case 1:
        textFile = "text1";
        break;
    case 2:
        textFile = "text2";
        break;
    case 3:
        textFile = "text3";
        break;
    case 4:
        textFile = "text4";
        break;
    default:
        exit(0);
    }
    
    return (textFile);
    
}



int main()
{
   
    std::string textFile = PickYourFile(); 
    std::string addTxt = ".txt"; // used to add to textFile to complete file name
    int numWordAppears = 0;
    std::ifstream bannedText("bannedwords.txt"); //file to read in of banned words and its path
    std::ifstream text1(textFile + addTxt); //file to read for text 1 and its path

    std::string text1Holder;
    std::vector <std::string> text1Vec;

    if (text1.is_open()) //Checks if file is there to open
    {
        while (text1 >> text1Holder) //reading each line including white space from the text1 file in to the varible text1holder
        {
            text1Vec.push_back(text1Holder);
            // std::cout << text1Holder << std::endl; //outputing varible

        }

    }
    else
    {
        std::cout << "Error, sorry file could not be found" << std::endl; // message if file cant be read.
        exit(0);
    }

    text1.close();

    std::cout << "\n\n";

    std::vector <std::string> bannedWords; // using a vector as it will dynamically increase memory as the number of banned words increase. the vected is of type string

    std::string listBannedWords; // where the word is held be for it is stored in the vector

    if (bannedText.is_open())
    {
        while (bannedText >> listBannedWords) // read in each line untill there is no more lines to read
        {
            bannedWords.push_back(listBannedWords); // places the word from the listBannedWords to the vector
        }
    }
    else
    {
        std::cout << "Error, sorry file could not be found" << std::endl; // message if file cant be read.
        exit(0);
    }

    bannedText.close();

    for (std::string bannedWords : bannedWords) // runs through the vectory and outputs each element out.
    {
        std::cout << bannedWords << std::endl;
    }

    IsCorrect();

    system("CLS");

    std::cout << "\n\n\n";

    int bannedListSize = bannedWords.size(); // placing the vectors size in to a vairble to use in a loop later

    int text1VecSize = text1Vec.size(); // placing vectors size in to a varible for later use


    int bannedWordsListNum = 0; // used for the belkow while loop.

    while (bannedWordsListNum < bannedListSize) // running through a loop to go through each banned word
    {
        for (int i = 0; i < text1VecSize; i++) // looping through each wored in the texted
        {
            std::string text1VecHolder1 = text1Vec[i]; // placing the vector in to a string varible to be transformed to lower case and then compared

            std::transform(text1VecHolder1.begin(), text1VecHolder1.end(), text1VecHolder1.begin(), ::tolower); // converting uppercase to lower case to compare

            if (text1Vec[i].find(bannedWords[bannedWordsListNum]) != -1) // checks to see if it can find the banned word inside another word if found it will return the postition
            {
                numWordAppears = numWordAppears + 1; // adding number of times banned word appears
                text1Vec[i] = "***"; // if position is found word will be replaced with the three stars
            }
          
            if (bannedWords[bannedWordsListNum] == text1VecHolder1) // condition for when banned word is found
            {
               numWordAppears = numWordAppears + 1; // adding number of times banned word appears
               text1Vec[i] = "***"; // replaces ***'s with banned word
            }


        }
     std::cout << bannedWords[bannedWordsListNum] << "  " << numWordAppears << std::endl; // prints out each banned word a space and the number of times it appears

     numWordAppears = 0; // resets counter to 0

     bannedWordsListNum = bannedWordsListNum + 1; // adds one more to the bannedWordsListNum for the while loop
    }

    std::string addFilter = "Filtered"; // used to complete saved file name
  
    // creating, opening and writing filtered message to file.
    std::ofstream filteredFile; 
    filteredFile.open(textFile + addFilter + addTxt); // opening/creating file;
    for (int i = 0; i < text1Vec.size(); ++i) // to go through each element 
    {
        filteredFile << text1Vec[i] << " "; // using " " to space out words outputting to file
    }
    filteredFile.close(); // closing file
   
    std::cout << "File has being filtered, please search for the text file in the wordfilter folder" << std::endl;

    return 0;

}


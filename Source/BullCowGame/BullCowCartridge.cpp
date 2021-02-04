// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    SetupGame();
    PrintLine(TEXT("The number of possible words is: %i"), Words.Num());
    PrintLine(TEXT("The hidden word is: %s."), *HiddenWord); // debug line

    for(int32 Index = 0; Index != 0; Index++)
    {
        PrintLine(TEXT("%s."), *Words[Index]);
    }
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    
    if(bGameOver)
    {
        ClearScreen();
        SetupGame();
    } else
    {
        ProccesGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    PrintLine(TEXT("Let's play Bull/Cow"));
    
    HiddenWord = TEXT("ukraine");
    Lives = HiddenWord.Len();
    bGameOver = false;
    
    PrintLine(TEXT("Guess %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Type your guess and press enter"));
    
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again"));
}

void UBullCowCartridge::ProccesGuess(FString Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have Won!"));
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Sorry wrong number of characters, try guessing again!"));
        PrintLine(TEXT("The word is %i characters long"), HiddenWord.Len());
        PrintLine(TEXT("You have %i lives remaining"), Lives);
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, try again"));
        return;
    }

    PrintLine(TEXT("Lost a life!"));
    PrintLine(TEXT("%i"), --Lives);

    if (Lives <= 0)
    {
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;   
    }
    
    // Show number of Bulls and Cows
    PrintLine(TEXT("Trying guessing again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word)
{

    for(int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index++; Comparison < Word.Len(); Comparison++)
        {
            if(Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    return true;
    
}
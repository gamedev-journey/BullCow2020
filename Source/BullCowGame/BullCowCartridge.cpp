// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    SetupGame();

    
    
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{   
    ProcessGuess(Input);
}   

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("coal");
    Lives = HiddenWord.Len();
    bGameOver = false;
    PrintLine(TEXT("Welcome to Bulls and Cows\n"));
    PrintLine(TEXT("Guess the %i letter word."), HiddenWord.Len());
    PrintLine(TEXT("Lives: %i"), Lives);
    PrintLine(TEXT("Type your answer\nand press enter to continue."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Please press enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {

        if (Guess == HiddenWord)
        {
            PrintLine(TEXT("Well done"));
            EndGame();
        }
        else
        {
            if (Guess.Len() != HiddenWord.Len())
            {
                PrintLine(TEXT("You are looking for a %i letter word."), HiddenWord.Len());
            }

            --Lives;
            if (Lives > 0)
            {
                PrintLine(TEXT("Please try again. Lives: %i"), Lives);
            }
            else
            {
                PrintLine(TEXT("You have no lives left."));
                EndGame();
            }
        }
    }
}
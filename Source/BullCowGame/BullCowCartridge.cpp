// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to Bulls and Cows\n"));
    PrintLine(TEXT("Guess the 4 letter word."));
    PrintLine(TEXT("Press enter to continue..."));
    HiddenWord = TEXT("coal");

    // set lives
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    

    if (Input == HiddenWord)
    {
        PrintLine(TEXT("Well done"));
    }
    else
    {
        PrintLine(TEXT("Better luck next time"));

       
    }

    // check if isogram
    // check number of characters
     // remove life
}   
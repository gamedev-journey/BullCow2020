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

    //const TCHAR HW[] = TEXT("cakes");

    IsIsogram(HiddenWord);

}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPlease press enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    

    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("Well done"));
        EndGame();
        return;
    }
       
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("You are looking for a %i letter word."), HiddenWord.Len());
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters please, guess again"));
        return;
    }


    --Lives;
    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left."));
        PrintLine(TEXT("The hidden word was %s."), *HiddenWord);
        EndGame();
    }
    
    PrintLine(TEXT("Please try again. Lives: %i"), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        PrintLine(TEXT("%c"), Word[Index]);
    }
    
    return true;
}
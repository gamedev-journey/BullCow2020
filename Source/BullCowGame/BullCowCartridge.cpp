// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
   
    Isogram = GetValidWords(Words);
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{   
    if (Input == "quit")
    {
        GIsRequestingExit = true;
    }
    else
    {
        ProcessGuess(Input);
    }
}   

void UBullCowCartridge::SetupGame()
{
    HiddenWord = Isogram[FMath::RandRange(0, Isogram.Num() - 1)];
    Lives = HiddenWord.Len() * 2;
    bGameOver = false;
    PrintLine(TEXT("Welcome to Bulls and Cows\n"));
    PrintLine(TEXT("Guess the %i letter word."), HiddenWord.Len());
    PrintLine(TEXT("Lives: %i"), Lives);
    PrintLine(TEXT("Press tab and yype your answer.\nPress enter to continue."));
    PrintLine(TEXT("Type quit to close the game."));
    
    //PrintLine(TEXT("The word is %s"), *HiddenWord);
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPlease press enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
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
    
    FBullCowCount Score = GetBullCows(Guess);

    PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);

    PrintLine(TEXT("Please try again. Lives: %i"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Comparison] == Word[Index])
            {
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;
    
    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}


FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	September 2021
//
//	Purpose:
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ROUNDMANAGER_H
#define ROUNDMANAGER_H

//#include "Main.h"
//#include "Bullseye.h"
#include "SA_Trainer.h"	// to include enums

class RoundManager {
	// Attributes
protected:
	int total_guesses = 0;
	int current_guess = 0;
	int bogey_count = 0;
	double distance_to_bullseye_ = 0;
	int hsd_range_ = 0;
	Coordinates my_aircraft_pos_ = { 0,0 };
	Coordinates bulls_pos_ = { 0,0 };
	Coordinates bogey_1_pos_ = { 0,0 };
	Coordinates bogey_2_pos_ = { 0,0 };
	Coordinates bogey_3_pos_ = { 0,0 };
	Coordinates mouse_click_pos_ = { 0,0 };
	Bullseye* bullseye_;
	Aircraft* my_aircraft_;
	Aircraft* bogeys[3] = { nullptr, nullptr, nullptr };
	ImageObject* hsd_distance_rings_ = nullptr;
	ImageObject* bearing_ring_ = nullptr;

public:
	using RoundState = SA_Trainer::RoundState; // creates an alias so I don't have to use SA_Trainer::RoundState
	using Difficulty = SA_Trainer::Difficulty;

	// Methods
protected:
	void CheckRecruitWinStatus(RoundState& state);
	void CheckCadetWinStatus(RoundState& state);
	void CheckRookieWinStatus(RoundState& state);
	void CheckVeteranWinStatus(RoundState& state);
	void CheckAceWinStatus(RoundState& state);
	bool IsClickInRectAroundBulls();

public:
	// constructor just creates object need a start and end round method to handle each round
	RoundManager(Aircraft* aircraft_Ptr, Bullseye* bullseye_Ptr, ImageObject* hsd_Ptr, ImageObject* bearing_ring_Ptr);
	~RoundManager();
	void CheckWinStatus(const Difficulty& level, RoundState& state, Coordinates mouse_click_position);
	void StartRound(const Difficulty& level, RoundState& state, Aircraft* bogeys[]);
	void ResetRound();
	int GetRemaingGuesses();
	int GetBullsDistance();
	int GetHSDRange();
};

#endif // ROUNDMANAGER_H

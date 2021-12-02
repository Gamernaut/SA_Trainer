//#include <iostream>
#include <string>
#include "RoundManager.h"
//#include "Main.h"
#include "SA_Trainer.h"
//#include "Bullseye.h"
//#include "Aircraft.h"

using namespace cpv;

RoundManager::RoundManager(Aircraft* aircraft_Ptr, Bullseye* bullseye_Ptr, ImageObject* hsd_Ptr, ImageObject* bearing_ring_Ptr) {
	// Setup all the relevant win data for this round
	bullseye_ = bullseye_Ptr;

	my_aircraft_ = aircraft_Ptr;
	my_aircraft_pos_.x = my_aircraft_->image_center_.x;
	my_aircraft_pos_.y = my_aircraft_->image_center_.y;

	hsd_distance_rings_ = hsd_Ptr;
	bearing_ring_ = bearing_ring_Ptr;
}

RoundManager::~RoundManager() {
	ResetRound();
}

void RoundManager::StartRound(const Difficulty& level, RoundState& state, Aircraft* bogeys[]) {
	// Set random bullseye position for this round
	bullseye_->SetRandomPosition();
	bulls_pos_.x = bullseye_->image_center_.x;
	bulls_pos_.y = bullseye_->image_center_.y;

	// Set random heading of my aircraft for this round and rotate HSD distance rings to match that heading
	my_aircraft_->SetRandomHeading();
	hsd_distance_rings_->RotateToFinalAngle(my_aircraft_->GetHeading());

	// Set the heading of the bearing ring to point to the bulls eye
	int bearing_to_bullseye = bullseye_->Bearing_FromPoint1ToPoint2(my_aircraft_->image_center_, bullseye_->image_center_);
	bearing_ring_->RotateToFinalAngle(bearing_to_bullseye);
	
	// Select a random HSD range from covering HSD scale of 5 miles to 240 miles
	int HSD_Range = (rand() % 160);

	if (HSD_Range <= 8) { hsd_range_ = 8; }
	else if (HSD_Range > 8 && HSD_Range <= 15) { hsd_range_ = 15; }
	else if (HSD_Range > 15 && HSD_Range <= 30) { hsd_range_ = 30; }
	else if (HSD_Range > 30 && HSD_Range <= 60) { hsd_range_ = 60; }
	else if (HSD_Range > 60 && HSD_Range <= 120) { hsd_range_ = 120; }
	else if (HSD_Range > 120 && HSD_Range <= 240) { hsd_range_ = 240; }

std::cout << "hsd_range_ set to =" << hsd_range_ << std::endl;

	// Now we have the HSD range calculate the distance to the bullseye and scale by range
	distance_to_bullseye_ = bullseye_->Distance_BetweenPoint1AndPoint2(my_aircraft_->image_center_, bullseye_->image_center_);
	
	// 320px is difference between center and outermost ring which equals the current range so work out proportion of that distance and multiply by scale
	// distance to bulls / 320 (total distance to outer ring at any scale) = proportion of full scale * HSD scale
	distance_to_bullseye_ = (distance_to_bullseye_ / 320) * hsd_range_;

	// Set a random position and heading for bogey's. We'll decide how many we want to use later
	bogeys[0]->SetRandomPosition();
	bogeys[0]->SetRandomHeading();
	bogey_1_pos_.x = bogeys[0]->GetPosition().x;
	bogey_1_pos_.y = bogeys[0]->GetPosition().y;
	bogey_1_heading_ = static_cast<int>(bogeys[0]->current_heading_);
	bogey_1_bulls_heading_ = bullseye_->Bearing_FromPoint1ToPoint2(bullseye_->image_center_, bogeys[0]->image_center_);
	bogey_1_bulls_distance_ = bullseye_->Distance_BetweenPoint1AndPoint2(bullseye_->image_center_, bogeys[0]->image_center_);
std::cout << "Bogey 1 heading = " << bogey_1_heading_ << ", Bulls distance = " << bogey_1_bulls_distance_ << " and bulls heading " << bogey_1_bulls_heading_ << std::endl;

	bogeys[1]->SetRandomPosition();
	bogeys[1]->SetRandomHeading();
	bogey_2_pos_.x = bogeys[1]->GetPosition().x;
	bogey_2_pos_.y = bogeys[1]->GetPosition().y;
	bogey_2_heading_ = static_cast<int>(bogeys[1]->current_heading_);
	bogey_2_bulls_heading_ = bullseye_->Bearing_FromPoint1ToPoint2(bullseye_->image_center_, bogeys[1]->image_center_);
	bogey_2_bulls_distance_ = bullseye_->Distance_BetweenPoint1AndPoint2(bullseye_->image_center_, bogeys[1]->image_center_);
std::cout << "Bogey 2 heading = " << bogey_2_heading_ << " and bulls heading " << bogey_2_bulls_heading_ << std::endl;


	bogeys[2]->SetRandomPosition();
	bogeys[2]->SetRandomHeading();
	bogey_3_pos_.x = bogeys[2]->GetPosition().x;
	bogey_3_pos_.y = bogeys[2]->GetPosition().y;
	bogey_3_heading_ = static_cast<int>(bogeys[2]->current_heading_);
	bogey_3_bulls_heading_ = bullseye_->Bearing_FromPoint1ToPoint2(bullseye_->image_center_, bogeys[2]->image_center_);
	bogey_3_bulls_distance_ = bullseye_->Distance_BetweenPoint1AndPoint2(bullseye_->image_center_, bogeys[2]->image_center_);
std::cout << "Bogey 3 heading = " << bogey_3_heading_ << " and bulls heading " << bogey_3_bulls_heading_ << std::endl;

	// How many bogeys for this round
	bogey_count = (std::rand() % 3);

	// Determine number of guesses, 3 guesses per bogey
	if (level == Difficulty::kAce) {

		// add 1 to bogey_count so it starts at 1 not zero and to include 3 as rand returns 0..2
		total_guesses = 3 * (bogey_count + 1);
	}
	else {
		total_guesses = 3;
	}

	// Now need to update the text in the display above the MDF with the info about the bogey so the user can use that info to determine
	// the correct location of the bogey

}

int RoundManager::GetRemaingGuesses() const {
	return total_guesses - current_guess;
}

int RoundManager::GetBullsDistance() const {
	return static_cast<int>(distance_to_bullseye_);
}

int RoundManager::GetHSDRange() const {
	return hsd_range_;
}

void RoundManager::ResetRound() {
	total_guesses = 0;
	current_guess = 0;
	bogey_count = 0;
	my_aircraft_pos_ = { 0,0 };
	bulls_pos_ = { 0,0 };
	bogey_1_pos_ = { 0,0 };
	bogey_2_pos_ = { 0,0 };
	bogey_3_pos_ = { 0,0 };
}

void RoundManager::CheckWinStatus(const Difficulty& level, RoundState& state, Coordinate mouse_click_position, int hsd_range_in) {
	current_guess += 1;
	
	std::cout << "current_guess = " << current_guess << std::endl;

	mouse_click_pos_ = mouse_click_position;

	//if (hsd_range_in != hsd_range_) {
	std::cout << "Range scale doesn't match. hsd_range_in = " << hsd_range_in << " and hsd_range_ = " << GetHSDRange() << ". distance_to_bullseye_ = " << distance_to_bullseye_ << std::endl;
	//	state = RoundState::kPlaying;
	//	return;
	//}

	if (current_guess <= total_guesses) {
		//Check the win condition for this round based on level of difficulty
		if (level == Difficulty::kAce) {
			CheckAceWinStatus(state);
		}
		else if (level == Difficulty::kCadet) {
			CheckCadetWinStatus(state);
		}
		else if (level == Difficulty::kRecruit) {
			CheckRecruitWinStatus(state);
		}
		else if (level == Difficulty::kRookie) {
			CheckRookieWinStatus(state);
		}
		else if (level == Difficulty::kVeteran) {
			CheckVeteranWinStatus(state);
		}
	}
}

void RoundManager::CheckRecruitWinStatus(RoundState& state) {
	// Win condition is to correctly identify the bearing of the bullseye from the aircraft (within a cone 30 deg wide, +/- 15 deg of the point clicked on)

	// Calculate the actual and guessed bearing
	int user_bearing_guess = bullseye_->Bearing_FromPoint1ToPoint2(my_aircraft_pos_, mouse_click_pos_);
	int actual_bearing = bullseye_->Bearing_FromPoint1ToPoint2(my_aircraft_pos_, bulls_pos_);

	// set State to win if the bearing is correct
	if (user_bearing_guess >= (actual_bearing - 15) && user_bearing_guess <= (actual_bearing + 15)) {
		state = RoundState::kWon;
	}
	// set State to playing if not correct and not last guess
	else if (current_guess < total_guesses) {
		state = RoundState::kPlaying;
		std::cout << "Keep going Recruit" << std::endl;
	}
	// set State to fail if this is the last guess and it's wrong
	else {
		state = RoundState::kFail;
		std::cout << "Better luck next time Recruit" << std::endl;
	}
}

void RoundManager::CheckCadetWinStatus(RoundState& state) {
	// Win condition same as recruit win condition but also range within +/- 20% of the HSD scale (i.e. +/- 16 miles on 80 mile range)

	// set State to win if the click is in the box +/- 15 deg either side as well as short of and long of the bulls eye
	if (IsClickInRectAroundBulls()) {
		std::cout << "Good guess cadet" << std::endl;
		state = RoundState::kWon;
	}
	// set State to playing if not correct and not last guess
	else if (current_guess < total_guesses) {
		state = RoundState::kPlaying;
		std::cout << "Keep going Cadet" << std::endl;
	}
	// set State to fail if this is the last guess and it's wrong
	else {
		state = RoundState::kFail;
		std::cout << "Better luck next time Cadet" << std::endl;
	}
}

void RoundManager::CheckRookieWinStatus(RoundState& state) {
	// Win condition is to correctly identify the bearing from the bullseye to the bogey

	// 	Calculate the actual and the user guessed bearing between the bullseye and the bogey
	int user_bearing_guess = bullseye_->Bearing_FromPoint1ToPoint2(bulls_pos_, mouse_click_pos_);
	int actual_bearing = bullseye_->Bearing_FromPoint1ToPoint2(bulls_pos_, bogey_1_pos_);

	// Set State to win if the guessed bearing is within +/- 15 deg of the actual bearing
	if (user_bearing_guess >= (actual_bearing - 15) && user_bearing_guess <= (actual_bearing + 15)) {
		state = RoundState::kWon;
		std::cout << "Good guess Rookie" << std::endl;
	}
	// set State to playing if not correct and not last guess
	else	if (current_guess < total_guesses) {
		state = RoundState::kPlaying;
		std::cout << "Keep going Rookie" << std::endl;
	}
	// set State to fail if this is the last guess and it's wrong
	else {
		state = RoundState::kFail;
		std::cout << "Better luck next time Rookie" << std::endl;
	}
}

void RoundManager::CheckVeteranWinStatus(RoundState& state) {
	// set State to win if the click within 32 pixels of the center of 1 bogey
	if (IsClickInRectAroundBogey(bogeys[0], nullptr)) {
		std::cout << "Good guess Veteran" << std::endl;
		state = RoundState::kWon;
	}
	// set State to playing if not correct and not last guess
	else if (current_guess < total_guesses) {
		state = RoundState::kPlaying;
		std::cout << "Keep going Veteran" << std::endl;
	}
	// set State to fail if this is the last guess and it's wrong
	else {
		state = RoundState::kFail;
		std::cout << "Better luck next time Veteran" << std::endl;
	}
}

void RoundManager::CheckAceWinStatus(RoundState& state) {
	// set State to win if the click within 32 pixels of the center of each bogey
	if (IsClickInRectAroundBogey(bogeys[0], bogeys[1])) {
		std::cout << "Good guess Ace" << std::endl;
		state = RoundState::kWon;
	}
	// set State to playing if not correct and not last guess
	else if (current_guess < total_guesses) {
		state = RoundState::kPlaying;
		std::cout << "Keep going Ace" << std::endl;
	}
	// set State to fail if this is the last guess and it's wrong
	else {
		state = RoundState::kFail;
		std::cout << "Better luck next time Ace" << std::endl;
	}
}

bool RoundManager::IsClickInRectAroundBulls() {
	int left_limit = bullseye_->image_center_.x - 32;
	int right_limit = bullseye_->image_center_.x + 32;
	int top_limit = bullseye_->image_center_.y - 32;
	int bottom_limit = bullseye_->image_center_.y + 32;

	std::cout << "left_limit = " << left_limit << " mouse x = " << mouse_click_pos_.x << " right limit" << right_limit << std::endl;
	std::cout << "top_limit = " << top_limit << " mouse y = " << mouse_click_pos_.y << " bottom limit" << bottom_limit << std::endl;

	if (mouse_click_pos_.x >= left_limit &&
		mouse_click_pos_.x <= right_limit &&
		mouse_click_pos_.y <= bottom_limit &&
		mouse_click_pos_.y >= top_limit) {
		return true;
	}
	else
	{
		return false;
	}
}

bool RoundManager::IsClickInRectAroundBogey(Aircraft* bogey1, Aircraft* bogey2) {
	int bogey_1_left_limit = bogey1->image_center_.x - 32;
	int bogey_1_right_limit = bogey1->image_center_.x + 32;
	int bogey_1_top_limit = bogey1->image_center_.y - 32;
	int bogey_1_bottom_limit = bogey1->image_center_.y + 32;

	// Check if there is a second aircraft, if not set the second data to the first ti simplify the if statements below
	int bogey_2_left_limit;
	int bogey_2_right_limit;
	int bogey_2_top_limit;
	int bogey_2_bottom_limit;

	if (bogey2 != nullptr) {
		bogey_2_left_limit = bogey2->image_center_.x - 32;
		bogey_2_right_limit = bogey2->image_center_.x + 32;
		bogey_2_top_limit = bogey2->image_center_.y - 32;
		bogey_2_bottom_limit = bogey2->image_center_.y + 32;
	}
	else {
		bogey_2_left_limit = bogey1->image_center_.x - 32;
		bogey_2_right_limit = bogey1->image_center_.x + 32;
		bogey_2_top_limit = bogey1->image_center_.y - 32;
		bogey_2_bottom_limit = bogey1->image_center_.y + 32;
	}

	
	std::cout << "bogey 1 left_limit = " << bogey_1_left_limit << " mouse x = " << mouse_click_pos_.x << " right limit" << bogey_1_right_limit << std::endl;
	std::cout << "bogey 1 top_limit = " << bogey_1_top_limit << " mouse y = " << mouse_click_pos_.y << " bottom limit" << bogey_1_bottom_limit << std::endl;

	if (mouse_click_pos_.x >= bogey_1_left_limit &&
		mouse_click_pos_.x <= bogey_1_right_limit &&
		mouse_click_pos_.y <= bogey_1_top_limit &&
		mouse_click_pos_.y >= bogey_1_bottom_limit &&
		mouse_click_pos_.x >= bogey_2_left_limit &&
		mouse_click_pos_.x <= bogey_2_right_limit &&
		mouse_click_pos_.y <= bogey_2_top_limit &&
		mouse_click_pos_.y >= bogey_2_bottom_limit) {
		return true;
	}
	else
	{
		return false;
	}
}

std::string RoundManager::AwacsCallString() {
	// TODO: Whole method is extremely inefficient way to do this, re-factor

	// First convert the bogey heading into a cardinal heading
	std::string bogey_heading;
	if (bogey_1_heading_ >= 337 && bogey_1_heading_ < 22) {
		bogey_heading = "North";
	}
	else if (bogey_1_heading_ >= 22 && bogey_1_heading_ < 67) {
		bogey_heading = "North East";
	}
	else if (bogey_1_heading_ >= 67 && bogey_1_heading_ < 112) {
		bogey_heading = "East";
	}
	else if (bogey_1_heading_ >= 112 && bogey_1_heading_ < 157) {
		bogey_heading = "South East";
	}
	else if (bogey_1_heading_ >= 157 && bogey_1_heading_ < 202) {
		bogey_heading = "South";
	}
	else if (bogey_1_heading_ >= 202 && bogey_1_heading_ < 247) {
		bogey_heading = "South West";
	}
	else if (bogey_1_heading_ >= 247 && bogey_1_heading_ < 292) {
		bogey_heading = "West";
	}
	else if (bogey_1_heading_ >= 292 && bogey_1_heading_ < 337) {
		bogey_heading = "North West";
	}
	else {
		bogey_heading = "Error: Unknown";
	}

	std::string awacs_call = "RM:Hostile group bulls ";
	awacs_call += std::to_string(bogey_1_bulls_heading_);
	awacs_call += " for ";
	awacs_call += std::to_string(bogey_1_bulls_distance_);
	awacs_call += ", Angels 20, tracking ";
	awacs_call += bogey_heading;
// std::cout << "awacs_call = " << awacs_call << std::endl;
	return awacs_call;
}
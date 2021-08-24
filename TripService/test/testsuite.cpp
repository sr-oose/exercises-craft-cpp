#include <gtest/gtest.h>

#include "TripServiceSupport.h"

TEST(TripService, getTripsByUserReturnsEmptyListForOneUser){
	//Init
	//TripService* service = new TripService();
	User user{1};

	//Call
	//std::list<Trip> resultlist = service->GetTripsByUser(&user);
	std::list<Trip> resultlist = TripService::GetTripsByUser(&user);

	//Verify
	ASSERT_EQ(0, resultlist.size());

	//Clean up
	//delete service;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

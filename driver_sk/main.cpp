#include <iostream>
#include <vector>
#include "gmock/gmock.h"
#include "device_driver.h"

#include "MockFlash.cpp"

using std::cout;
using std::vector;

using namespace testing;

class Test_Fixture : public Test {
public:
	NiceMock<MockFlash> mockFlash;;
	FlashMemoryDevice* hardware = &mockFlash;
	DeviceDriver driver{ hardware };
};

TEST_F(Test_Fixture, Read5times) {
//	MockFlash mockFlash;	
	// EXPECT times
	// stub 1,2,3,4,5
	// exception이 발생되어야해

	EXPECT_CALL(mockFlash, read)
		.Times(5)
		.WillOnce(Return(0))
		.WillOnce(Return(1))
		.WillOnce(Return(0))
		.WillOnce(Return(0))
		.WillOnce(Return(1));
	
	int data, backup;
	for (int i = 0; i < 5; i++) {
		data = driver.read(0xFF);
		if (i == 0) backup = data;

		if (data != backup) std::cout<<"ERROR\n";
	}
	
	 
	//EXPECT_EQ(0, data);
}

/*
TEST(DeviceDriver, ReadFromHW) {
	// TODO : replace hardware with a Test Double
	FlashMemoryDevice* hardware = nullptr;
	DeviceDriver driver{ hardware };
	int data = driver.read(0xFF);
	EXPECT_EQ(0, data);
}
*/

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
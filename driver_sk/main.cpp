#include "gmock/gmock.h"
#include "device_driver.h"

using namespace testing;

class FlashMock : public FlashMemoryDevice {
public:
    MOCK_METHOD(unsigned char, read, (long address), (override));
    MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(TS, TC2) {
    FlashMock mockHW;
    DeviceDriver dd{ &mockHW };

    EXPECT_CALL(mockHW, read((long)0xA))
        .WillOnce(Return((int)0xDD))
        .WillOnce(Return((int)0xDD))
        .WillOnce(Return((int)0xDD))
        .WillOnce(Return((int)0xDD))
        .WillOnce(Return((int)0xDA));

    EXPECT_THROW(dd.read(0xA), std::exception);
}

TEST(TS, TC1) {
    FlashMock mockHW;
    DeviceDriver dd{ &mockHW }; //mock injection

    EXPECT_CALL(mockHW, read((long)0xA))
        .Times(5)
        .WillRepeatedly(Return((int)0x77));

    int result = dd.read(0xA);
}

int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}
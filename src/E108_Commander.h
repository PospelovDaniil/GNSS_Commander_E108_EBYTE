#ifndef E108_COMMANDER_H
#define E108_COMMANDER_H
#include "pmtk.h"

/**
 * @brief makeCmd
 * @param str GOOD - PGKC030,1,2, BAD - $PGKC030,1,2*2F\r\n
 * @param len
 * @return
 */
std::string makeCmd(const std::string &str)
{
    if(str.empty()) return {};
    char buff[5];
    sprintf(buff, "*%X", getContolSum(str));
    std::string res("$");
    res += str;
    res += std::string(buff); // FIXME so bad, no think
    res += '\r'; res += '\n';
    return res;
}

/**
 * @brief makeCmd
 * @param str GOOD - PGKC030,1,2, BAD - $PGKC030,1,2*2F\r\n
 * @param len
 * @return
 */
const char *const makeCmd(const char *str, const u8 len)
{
    if(!len) return nullptr;
    char *const res = new char[7 + len]; // 7: % + * + 2byte_hex + \r + |n + \0
    sprintf(res, "$%s*%0*X\r\n", str, 2, getContolSum(str, len));
    return res;
}

// https://www.cdebyte.com/Uploadfiles/Files/2022-7-6/2022761056555773.pdf
// Pre-calculated some cmd's E108-EBYTE
// Command 030: System reboot command
#define E108_SYS_REBOOT_WARM_BOOT_SOFT_REBOOT       "$PGKC030,1,1*2C\r\n"
#define E108_SYS_REBOOT_WARM_START_SOFT_REBOOT      "$PGKC030,2,1*2F\r\n"
#define E108_SYS_REBOOT_COLD_BOOT_SOFT_REBOOT       "$PGKC030,3,1*2E\r\n"
#define E108_SYS_REBOOT_FULL_COLD_START_SOFT_REBOOT "$PGKC030,4,1*29\r\n"
#define E108_SYS_REBOOT_WARM_BOOT_HARD_REBOOT       "$PGKC030,1,2*2F\r\n"
#define E108_SYS_REBOOT_WARM_START_HARD_REBOOT      "$PGKC030,2,2*2C\r\n"
#define E108_SYS_REBOOT_COLD_BOOT_HARD_REBOOT       "$PGKC030,3,2*2D\r\n"
#define E108_SYS_REBOOT_FULL_COLD_START_HARD_REBOOT "$PGKC030,4,2*2A\r\n"
#define E108_SYS_REBOOT_WARM_BOOT_CLEAR             "$PGKC030,1,3*2E\r\n"
#define E108_SYS_REBOOT_WARM_START_CLEAR            "$PGKC030,2,3*2D\r\n"
#define E108_SYS_REBOOT_COLD_BOOT_CLEAR             "$PGKC030,3,3*2C\r\n"
#define E108_SYS_REBOOT_FULL_COLD_START_CLEAR       "$PGKC030,4,3*2B\r\n"

// Command 040: Erases ancillary information from flash
#define E108_ERASE_ANCILLARY_INFO_FLASH             "$PGKC030,4,3*2B\r\n"

/*
 * The command can be woken up by sending any command, invalid commands
 * can also be, the hardware can be woken up by plugging and unplugging
 * the serial port, and the original low-power command can be sent directly.
 */
// Command 051: Enter standby low-power: mode
#define E108_ENTER_STANBY_LOW_POWER                 "$PGKC051,0*37\r\n"

/*
 * The command is set to output NMEA data every 1000ms, that is, 1s.
 * Note: When setting the message interval output above 2HZ,
 * firstincrease the baud rate to more than 115200 to ensure
 * the high-frequencyNMEA message output, the command is not saved in Flash,
 * Afterpowerloss, it reverts to the original NMEA output frequency.
 */
// Command 101: Configure the interval (in ms) at which NMEA messages are output
#define E108_CONFIGURE_INTERVAL_NMEA_MSG_100        "$PGKC101,100*32\r\n"
#define E108_CONFIGURE_INTERVAL_NMEA_MSG_500        "$PGKC101,500*36\r\n"
#define E108_CONFIGURE_INTERVAL_NMEA_MSG_1000       "$PGKC101,1000*02\r\n"

// Command 105: Enter a periodic low-power mode . MAKED LATER, USE makeCmd()

/*
 * Note: Although the single Galileo mode command is set to $PG
 * KC115,0 , 0,0,1*2 B can send successfully but is currently G K
 * 9501 Firmware does not yet support Galileo star search mode
 */
// Command 115: Set the star search
#define E108_STAR_SEARCH_ALL                        "$PGKC115,1,1,1,1*2A\r\n"
#define E108_STAR_SEARCH_GPS                        "$PGKC115,1,0,0,0*2B\r\n"
#define E108_STAR_SEARCH_GLONASS                    "$PGKC115,0,1,0,0*2B\r\n"
#define E108_STAR_SEARCH_GPS_GLONASS                "$PGKC115,1,1,0,0*2A\r\n"
#define E108_STAR_SEARCH_GPS_GLONASS_BEIDU          "$PGKC115,1,1,1,0*2B\r\n"

/*
 * The difference between command115 and 121 commands is that the 115
 * command will not be saved in flash after setting, the star search
 * mode set after restart will disappear, and the command setting of 121
 * will be saved in flash. The star search mode set after the restart
 * will be retained, and neither 115 nor 121 supports the Galileo galaxy.
 */
// Command 121: Set the star search mode and save to flash
#define E108_STAR_SEARCH_FLASH_ALL                  "$PGKC121,1,1,1,1*2D\r\n"
#define E108_STAR_SEARCH_FLASH_GPS                  "$PGKC121,1,0,0,0*2C\r\n"
#define E108_STAR_SEARCH_FLASH_GLONASS              "$PGKC121,0,1,0,0*2C\r\n"
#define E108_STAR_SEARCH_FLASH_GPS_GLONASS          "$PGKC121,1,1,0,0*2D\r\n"
#define E108_STAR_SEARCH_FLASH_GPS_GLONASS_BEIDU    "$PGKC121,1,1,1,0*2C\r\n"

// Command 146: Set the serial port input and output format and baud rate
#define E108_SET_SERIAL_IO_BAUD_RATE_9600           "$PGKC146,3,3,9600*0F\r\n"
#define E108_SET_SERIAL_IO_BAUD_RATE_115200         "$PGKC146,3,3,115200*07\r\n"
#define E108_SET_SERIAL_IO_BAUD_RATE_921600         "$PGKC146,3,3,921600*0C\r\n"

// Command 239: Turns the SBAS feature on or off
#define E108_SBAS_ON                                "$PGKC239,1*3A\r\n"
#define E108_SBAS_OFF                               "$PGKC239,0*3B\r\n"

// Command 786: Set the positioning mode
#define E108_SET_POSITIONING_MODE_NORMAL            "$PGKC786,0*3A\r\n"
#define E108_SET_POSITIONING_MODE_FITNESS           "$PGKC786,1*3B\r\n"
#define E108_SET_POSITIONING_MODE_AERO              "$PGKC786,2*38\r\n"
#define E108_SET_POSITIONING_MODE_BALLOON           "$PGKC786,3*39\r\n"



#endif // E108_COMMANDER_H

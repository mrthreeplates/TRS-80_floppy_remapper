/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.79.0
        Device            :  PIC18F26Q10
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include <xc.h>
#include "mcc_generated_files/mcc.h"

// Use curiosity High Pin Count proto board w/PIC18F47Q10
// instead of a PIC18F26Q10
//#define PROTO

// Undefine to avoid extra writes during debugging
#define EEPROM

// Define to test post unit-test behaviors
//#define FORCE_M4P
//#define FORCE_NOT_M4P

// Define one of the following to determine MotorOn pin behavior
#define MOTORON_D01
//#define MOTORON_D23
//#define MOTORON_IE

#define ERASED_DATA 0xff
#ifdef EEPROM
// Initialize the first 8 bytes of the EEPROM after every re-flash
__EEPROM_DATA(ERASED_DATA, ERASED_DATA, ERASED_DATA, ERASED_DATA,
              ERASED_DATA, ERASED_DATA, ERASED_DATA, ERASED_DATA);
#endif

// EEPROM addresses (out of 256 bytes)
// (must be at least 3 bytes apart due to redundant copies)
#define NUM_COPIES  3
const uint16_t default_map_address = 0;
const uint16_t unit_test_address = 4;

#define INVALID_MAP (ERASED_DATA)
#define NO_MAP      0

#define NUM_MAPS    (1<<3)          // 3 bits used for the map, or 8 total
#define LAST_MAP    (NUM_MAPS-1)
#define MAP_MASK    (LAST_MAP)

#define NUM_DRIVES  4

volatile uint8_t default_map;
volatile uint8_t enabled_map;
volatile uint8_t current_map;

const uint8_t mapping[NUM_MAPS][NUM_DRIVES] = {
    {0, 1, 2, 3},           // index 0 (NO_MAP)
    {1, 0, 2, 3},           // index 1
    {2, 0, 1, 3},           // index 2
    {3, 0, 1, 2},           // index 3
    {0, 2, 1, 3},           // index 4
    {1, 2, 0, 3},           // index 5
    {2, 3, 0, 1},           // index 6
    {3, 2, 0, 1}            // index 7 (LAST_MAP)
};

// R/W PIN aliases
#define DS2_OUT     PORTCbits.RC0
#define DS2_IN      LATC1
#define DS1_OUT     PORTCbits.RC2
#ifdef PROTO
#define DS1_IN      LATD0
#else
#define DS1_IN      LATC3
#endif
#define DS0_IN      LATC4
#define DS0_OUT     PORTCbits.RC5
#define DS3_IN      LATC6
#define DS3_OUT     PORTCbits.RC7

#define CLK         LATB0
#define SDSEL_OUT   PORTBbits.RB1
#define SDSEL_IN    LATB2
#define DDEN_IN     LATB3
#define DDEN_OUT    PORTBbits.RB4
#define ENABLE_W    LATB5
#define ENABLE      PORTBbits.RB5
#define NOT_M4P     PORTBbits.RB7
// Because RB6/7 are used as inputs during debugging, we can't read
// the pin directly via PORTBbits.RB7, so use CLC7out instead.
#define EXTBUS      CLC7_OutputStatusGet()

#define LED_MAP_B2  LATA0
#define LED_MAP_B1  LATA1
#define LED_MAP_B0  LATA2
#define LED_DEFAULT LATA3
#define LED_ENABLED LATA4
#define NOT_MOTORON_D1 LATA5
#define NOT_CLR     LATA6
#define NOT_MOTORON_D0 LATA7

// RB6 is normally an output, but a debugger forces it to be an input
// So we can use this as a test.  Is there a better way?
#define DEBUGGER_ATTACHED (TRISB & BIT(6))

// redundant eeprom read / write byte routines.
uint8_t read_eeprom(uint16_t address, uint8_t error_val) {
#ifdef EEPROM
    uint8_t val[NUM_COPIES];
    for (int i = 0; i < NUM_COPIES; i++)
        val[i] = DATAEE_ReadByte(address++);
    if (val[0] == val[1] || val[0] == val[2])
        return val[0];
    if (val[1] == val[2])
        return val[1];
    return error_val;
#else
    return ERASED_DATA;
#endif

}

void write_eeprom(uint16_t address, uint8_t val) {
#ifdef EEPROM
    for (int i = 0; i < NUM_COPIES; i++)
        DATAEE_WriteByte(address++, val);
#endif
}

void init_default_map(void) {
    uint8_t map = read_eeprom(default_map_address, INVALID_MAP);
    if (map > LAST_MAP)
        map = NO_MAP;
    default_map = map;
}

void set_default_map(uint8_t map) {
    if (map > LAST_MAP)
        map = NO_MAP;
    write_eeprom(default_map_address, map);
    default_map = map;
}

#define OUT_DS0 CLC1SEL1
#define OUT_DS1 CLC2SEL1
#define OUT_DS2 CLC5SEL1
#define OUT_DS3 CLC6SEL1

#define DS0_CLCIN 1 // (CLCIN1)
#define DS1_CLCIN 3 // (CLCIN3)
#define DS2_CLCIN 4 // (CLCIN4)
#define DS3_CLCIN 5 // (CLCIN5)

const uint8_t ds_clcin[] = {DS0_CLCIN, DS1_CLCIN, DS2_CLCIN, DS3_CLCIN};

// Change the drive mapping by reprogramming the CLC blocks.
void set_current_map(uint8_t map) {
    if (map > LAST_MAP)
        map = NO_MAP;

    for (int ds = 0; ds < NUM_DRIVES; ds++) {
        uint8_t clcin = ds_clcin[ds];
        switch (mapping[map][ds]) {
            case 0: OUT_DS0 = clcin; break;
            case 1: OUT_DS1 = clcin; break;
            case 2: OUT_DS2 = clcin; break;
            case 3: OUT_DS3 = clcin; break;                
        }
    }

    current_map = map;
}

#define WAIT    __delay_us(1)   // brief wait
#define PAUSE   __delay_ms(250) // longer wait
#define BIT(x) (1 << (x))

// Store blink pattern in reverse, terminated by a leading 1.
volatile uint16_t blink_pattern = 0b100001111;    // slow on/off toggle.
volatile uint16_t blink_val = 1;

void blink_map_leds(uint8_t map, bool reset) {    
    if (reset || blink_val <= 1) {
        blink_val = blink_pattern;
    }
    bool set = blink_val & 1;
    blink_val >>= 1;
 
    LED_MAP_B0 = (((map & BIT(0)) > 0) && set);
    LED_MAP_B1 = (((map & BIT(1)) > 0) && set);
    LED_MAP_B2 = (((map & BIT(2)) > 0) && set);
}

void set_map_leds(void) {
    bool enabled = ENABLE;
    uint8_t map = enabled ? enabled_map : NO_MAP;

    if (map != current_map)
        set_current_map(map);

    LED_DEFAULT = (map == default_map);
    LED_ENABLED = enabled;

    blink_map_leds(map, true);
}

void row_timer(void) {
    blink_map_leds(current_map, false);
}

// Clear CLC1-6 via external pin
void external_clr(void) {
    NOT_CLR = 1;
    WAIT;
    // falling edge clears
    NOT_CLR = 0;
    WAIT;
    NOT_CLR = 1;
}

// Clear CLC1-6 via CLC8
void internal_clr(void) {
    CLC8POL = 0;
    WAIT;
    // set CLC8 high
    CLC8POL = BIT(7);
    WAIT;
    CLC8POL = 0x0;

    // Clear MotorOn
    NOT_MOTORON_D1 = NOT_MOTORON_D0 = 1; 
}

// latch CLC1-6 flip flops
void clk(void) {
    CLK = 0;
    WAIT;
    // rising edge latches
    CLK = 1;
    WAIT;
    CLK = 0;
}

void enable(bool enabled) {
    ENABLE_W = enabled;
    WAIT;
}

// flip flop bits mapped into the CLCDATA register
#define CLC_DS0     BIT(0)  // ff bit 0 (i.e. from OUT instruction)
#define CLC_DS1     BIT(1)  // ff bit 1
#define CLC_DS2     BIT(4)  // ff bit 2
#define CLC_DS3     BIT(5)  // ff bit 3
#define CLC_SDSEL   BIT(2)  // ff bit 4
#define CLC_DDEN    BIT(3)  // ff bit 7
#define CLC_ALL     (CLC_DS0|CLC_DS1|CLC_DS2|CLC_DS3|CLC_SDSEL|CLC_DDEN)

#define FF_SET_FLAG         (CLC_DS0|CLC_DS1)
#define FF_SET_MAP(x)       (((x) & FF_SET_FLAG) == FF_SET_FLAG)
#define FF_TO_MAP(x)        (((x) >> 2) & MAP_MASK)
#define CLC_SET_DEFAULT(x)  ((x) & CLC_DDEN)

volatile int isr_count = 0;
volatile bool m4p = false;

void ISR(void) {
    // read latched CLC outputs in parallel.
    uint8_t clc = CLCDATA;
    isr_count++;

    // DS2 & DS3 are inverted in m4p mode.
    if (m4p)
        clc ^= (CLC_DS2|CLC_DS3);

    // MotorOn should follow each drive select
#ifdef MOTORON_D01
    // Generate MotorOn for Internal Drives 0 or 1
#define DSMAP(ds) (ds)
    if (clc & CLC_DS0) NOT_MOTORON_D0 = 0;
    if (clc & CLC_DS1) NOT_MOTORON_D1 = 0;
#elif defined(MOTORON_D23)
    // Generate MotorON for External Drives 2 or 3
#define DSMAP(ds) ((ds) ^ 2)
    if (clc & CLC_DS2) NOT_MOTORON_D0 = 0;
    if (clc & CLC_DS3) NOT_MOTORON_D1 = 0;
#elif defined(MOTORON_IE)
    // Generate MotorON for Internal or External drive sets
#define DSMAP(ds) ((ds) >> 1)
    if (clc & (CLC_DS0|CLC_DS1)) NOT_MOTORON_D0 = 0;
    if (clc & (CLC_DS2|CLC_DS3)) NOT_MOTORON_D1 = 0;
#else
#error "pick one!"
#endif
    
    // If a single drive is active, don't do anything!
    // We don't want the disable switch to change the map while in use.
    switch (clc & (CLC_DS0|CLC_DS1|CLC_DS2|CLC_DS3)) {
        case CLC_DS0:
        case CLC_DS1:
        case CLC_DS2:
        case CLC_DS3:
            return;
        case 0:
            // Only clear MotorOns when all drives become inactive
            NOT_MOTORON_D1 = NOT_MOTORON_D0 = 1;
        // else fall-through
    }

    // We need the map to unscramble the clc bits
    if (current_map > LAST_MAP)
        return;
    
    // unscramble clc data into flip flop outputs (except for DDEN)
    // this will give us the set map flag and our new mapping.
    uint8_t ff = 0;
    uint8_t b = 1;
    for (int ds = 0; ds < NUM_DRIVES; ds++) {
        switch (mapping[current_map][ds]) {
            case 0: if (clc & CLC_DS0) ff |= b; break;
            case 1: if (clc & CLC_DS1) ff |= b; break;
            case 2: if (clc & CLC_DS2) ff |= b; break;
            case 3: if (clc & CLC_DS3) ff |= b; break;
        }
        b <<= 1;
    }
    if (clc & CLC_SDSEL) ff |= b;

    if (FF_SET_MAP(ff)) {
        // Clear outputs since more than one drive enabled is an
        // invalid h/w condition.  Should be < 5us.
        internal_clr();
        enabled_map = FF_TO_MAP(ff);
        if (CLC_SET_DEFAULT(clc)) {
            set_default_map(enabled_map);
        }
        // fall-through
    }

    // Always update the map and leds since disable could have been
    // switched while a drive was active (deferring the map change until
    // the next interrupt.
    set_map_leds();
}

void mapper_init(void) {
    init_default_map();
    enabled_map = default_map;
    current_map = INVALID_MAP;

    set_map_leds();
    
    internal_clr();
 
    IOCAF6_SetInterruptHandler(&ISR);
    IOCBF0_SetInterruptHandler(&ISR);
    IOCBF5_SetInterruptHandler(&ISR);
}

void set_m4p(void) {
    m4p = true;
    // Change DS2,3 to be active low since there is no inverter/driver.
    CLC5POL = CLC6POL = BIT(7);
    // For use on M4P Non-gate array only:
    //   Change ExtBus to drive HLT/RDY of the 1793 FDC
    //   (DS0 | DS1 | ~DS2 | ~DS3).
    CLC7GLS0 = 0x5A;
    // possibly inverted, depending on where we want to jumper the signal.
    // CLC7POL = BIT(7);
}

// enable support for drives 2 and 3 on a M4P
// including signal needed for M4P non-GA
void enable_m4p(void) {
    set_m4p();
    // Change DS2,3 to be open drain (w/max sink current of 48ma)
    // This is only done on boot, not during unit testing.
    ODCONC = (BIT(0) | BIT(7));

    // Change blink pattern to a quick double flash and pause
    blink_pattern = 0b10000101;
}

// Flash LED_ENABLED slowly (with others on) indicating unit tests passed
void pass_halt(void) {
    LED_DEFAULT = LED_MAP_B0 = LED_MAP_B1 = LED_MAP_B2 = true;
    while (1) {
        LED_ENABLED = !LED_ENABLED;
        PAUSE; PAUSE;
    }
}

// Alternately Flash all leds indicating unit tests failed.
void error_halt(void) {
   while (1) {
        LED_ENABLED = LED_DEFAULT = !LED_ENABLED;
        LED_MAP_B0 = LED_MAP_B1 = LED_MAP_B2 = !LED_ENABLED;
        PAUSE;
    }
}

#define UNIT_PASS   0
#define UNIT_FAIL   1
#define RUN_TESTS   2

void check(bool ok) {
    if (ok)
        return;
    
    di();
    write_eeprom(unit_test_address, UNIT_FAIL);
    error_halt();
}

void check_leds(uint8_t map, bool is_enabled, bool is_default) {
    check(LED_MAP_B0 == ((map & BIT(0)) > 0));
    check(LED_MAP_B1 == ((map & BIT(1)) > 0));
    check(LED_MAP_B2 == ((map & BIT(2)) > 0));

    check(LED_ENABLED == is_enabled);
    check(LED_DEFAULT == is_default);
}

// Setup for running unit tests once, on the first boot after programming.
// Assume the device is not yet installed in computer
// (inputs will be floating, outputs are disconnected).
// Also, this needs to run before interrupts are enabled so that inputs
// will be in a known state before the system and leds are initialized.
uint8_t setup_tests(void) {
    uint8_t status = read_eeprom(unit_test_address, UNIT_FAIL);
    if (status == UNIT_PASS || status == UNIT_FAIL)
        return status;      // tests ran previously, don't run them again.

    // Switch inputs to outputs so we can control them during unit testing.
    // Note: B6 and B7 will remain as inputs in debug mode
    TRISA &= ~BIT(6);
    TRISB &= ~(BIT(0)| BIT(2) | BIT(3) | BIT(5) | BIT(7));
    TRISC &= ~(BIT(1)| BIT(3) | BIT(4) | BIT(6));
#ifdef PROTO
    TRISD &= ~BIT(0);  // in lieu of C3
#endif
    // initialize inputs
    ENABLE_W = 1;
    NOT_CLR = 1;

    return RUN_TESTS;
}

// set all 6 inputs of the FF at once for unit testing.
void set_inputs(bool val) {
    DS0_IN = DS1_IN = DS2_IN = DS3_IN = SDSEL_IN = DDEN_IN = val;
}

#define NO_DS   -1
#define ALL_DS  0xf

// Check that only one of DS0,1,2, or 3 is set (and EXTBUS)
void check_outs(int ds, bool sdsel_exp, bool dden_exp) {
    switch (ds) {
        case NO_DS:     // No DS should be set (and !EXTBUS)
            check(!DS0_OUT && !DS1_OUT && (DS2_OUT == m4p) && \
                  (DS3_OUT == m4p) && !EXTBUS);
            break;
        case 0:
            check(DS0_OUT && !DS1_OUT && (DS2_OUT == m4p) && \
                  (DS3_OUT == m4p) && (EXTBUS == m4p));
            break;
        case 1:
            check(!DS0_OUT && DS1_OUT && (DS2_OUT == m4p) && \
                  (DS3_OUT == m4p) && (EXTBUS == m4p));
            break;
        case 2:
            check(!DS0_OUT && !DS1_OUT && (DS2_OUT != m4p) && \
                  (DS3_OUT == m4p) && EXTBUS);
            break;
        case 3:
            check(!DS0_OUT && !DS1_OUT && (DS2_OUT == m4p) && \
                  (DS3_OUT != m4p) && EXTBUS);
            break;
        case ALL_DS:    // All DS should be set (and EXTBUS)
            check(DS0_OUT && DS1_OUT && (DS2_OUT != m4p) && \
                  (DS3_OUT != m4p) && EXTBUS);
            break;
    }
    check(SDSEL_OUT == sdsel_exp && DDEN_OUT == dden_exp);
}

void check_maps(uint8_t curr_exp, uint8_t enable_exp, uint8_t default_exp) {
    check(current_map == curr_exp && enabled_map == enable_exp && \
          default_map == default_exp);
}

void check_clc(void) {
    check((CLCDATA & CLC_ALL) == (m4p ? (CLC_DS2|CLC_DS3) : 0));
}

void set_cmd(uint8_t map, bool set_default) {
    // flag for the set map command
    DS0_IN = DS1_IN = 1;

    // encode map in DS2,3 and SDSEL
    DS2_IN = (map & BIT(0)) ? 1 : 0;
    DS3_IN = (map & BIT(1)) ? 1 : 0;
    SDSEL_IN = (map & BIT(2)) ? 1 : 0;

    // Set DDEN if we are to set the default map too.
    DDEN_IN = set_default;
}

void set_drive(uint8_t ds) {
    set_inputs(0);
    switch (ds) {
        case 0: DS0_IN = 1; break;
        case 1: DS1_IN = 1; break;
        case 2: DS2_IN = 1; break;
        case 3: DS3_IN = 1; break;
    }
    clk();
}

void unit_tests(void) {
    uint8_t map;

    // disable interrupts so ISR can't interfere with testing
    di();
    // ignore spurious interrupts before we begin.
    check (isr_count <= 3);
    int isr_exp = isr_count;

    // verify maps are set as per defaults
    check_maps(NO_MAP, NO_MAP, NO_MAP);

    // verify EEPROM is erased
    check(read_eeprom(default_map_address, 0) == ERASED_DATA);
    check(read_eeprom(unit_test_address, 0) == ERASED_DATA);

    // Check inputs and outputs are low
    // (can't check !NOT_M4P as we are connected to a debugger.)
    check(!DS0_IN && !DS0_OUT && !DS1_IN && !DS1_OUT &&
          !DS2_IN && !DS2_OUT && !DS3_IN && !DS3_OUT &&
          !SDSEL_IN && !SDSEL_OUT && !DDEN_IN && !DDEN_OUT &&
          !EXTBUS && ENABLE && !CLK && NOT_CLR);

    check(NOT_MOTORON_D0 && NOT_MOTORON_D1);
    
    // check initial LED outputs are set correctly
    check(LED_ENABLED && LED_DEFAULT && \
          !LED_MAP_B0 && !LED_MAP_B1 && !LED_MAP_B2);

    for (int mode = 0; mode < 2; mode++) {
        if (mode == 1)
            set_m4p();

        // Check drive mapping (e.g. CLC1,2,5,6 and 7 logic))
        for (map = 0; map < NUM_MAPS; map++) {
            set_current_map(map);
            for (int ds = 0; ds < NUM_DRIVES; ds++) {
                set_drive(ds);
                check_outs(mapping[map][ds], false, false);
            }
        }

        // Check SDSEL (CLC3)
        set_inputs(0);
        SDSEL_IN = 1;
        clk();
        check_outs(NO_DS, true, false);

        // Check DDEN (CLC4)
        set_inputs(0);
        DDEN_IN = 1;
        clk();
        check_outs(NO_DS, false, true);

        // Check both clear functions for CLC 1-6
        set_inputs(1);
        for (int i = 0; i < 2; i++) {
            clk();
            check_outs(ALL_DS, true, true);
            if (i)
                internal_clr();
            else
                external_clr();
            check_outs(NO_DS, false, false);
        }
        set_inputs(0);

        ei(); WAIT; di();
        // Ignore interrupts triggered by our testing above.
        // We expect one for the external clear and another for external clk.
        // Disable shouldn't have been touched.
        check (isr_count == (isr_exp + 2));
        isr_exp = isr_count;
    
        // Check ISR functions
        for (map = 0; map < NUM_MAPS; map++) {
            // Verify set map command (with enable)
            check(ENABLE);
            enabled_map = default_map = INVALID_MAP;
            set_cmd(map, false);
            ei(); clk(); di(); isr_exp++; 
            check_clc();
            check_maps(map, map, INVALID_MAP);
            check_leds(map, true, false);
            PAUSE;

            // Verify save default option (still with enable)
            enabled_map = default_map = INVALID_MAP;
            set_cmd(map, true);
            ei(); clk(); di(); isr_exp++;
            check_clc();
            check_maps(map, map, map);
            check_leds(map, true, true);
            PAUSE;

            // Verify disable
            ei(); enable(false); di(); isr_exp++;
            check_maps(NO_MAP, map, map);
            check_leds(NO_MAP, false, (map == NO_MAP));
            PAUSE;

            // verify re-enable
            ei(); enable(true); di(); isr_exp++;
            check_maps(map, map, map);
            check_leds(map, true, true);
            PAUSE;
        }
        set_inputs(0);

        // check that we processed the expected number of interrupts
        ei(); WAIT; di();
        check (isr_count == isr_exp);
    }

    // Check deferred disable behavior
    ei();
    for (int ds = 0; ds < NUM_DRIVES; ds++) {
        enable(true);
        set_drive(ds);
        check(current_map == LAST_MAP);

        // Disable shouldn't change the mapping while drives are in use.
        enable(false);
        check(current_map == LAST_MAP);

        // A clear should cause the disable to take effect.
        external_clr();
        check(current_map == NO_MAP);
    }

    // Check MotorOn outputs and behavior.
    // (with mapping disabled and interrupts enabled)

    // Simulate accessing one drive at a time.
    for (int ds = 0; ds < NUM_DRIVES; ds++) {
        check(NOT_MOTORON_D0 && NOT_MOTORON_D1);
        set_drive(ds);
        switch(DSMAP(ds)) {
            case 0: check(!NOT_MOTORON_D0 && NOT_MOTORON_D1); break;
            case 1: check(NOT_MOTORON_D0 && !NOT_MOTORON_D1); break;
            case 2: check(NOT_MOTORON_D0 && NOT_MOTORON_D1); break;
            case 3: check(NOT_MOTORON_D0 && NOT_MOTORON_D1); break;
        }
        external_clr();
    }

    // Simulate accessing drives sequentially
    // (validating the sticky behavior of MotorOn)
    check(NOT_MOTORON_D0 && NOT_MOTORON_D1);
    for (int ds = 0; ds < NUM_DRIVES; ds++) {
        set_drive(ds);
#ifdef MOTORON_D23      // Need to special case this, unfortunately
        switch(ds) {
            case 0: check(NOT_MOTORON_D0 && NOT_MOTORON_D1); break;
            case 1: check(NOT_MOTORON_D0 && NOT_MOTORON_D1); break;
            case 2: check(!NOT_MOTORON_D0 && NOT_MOTORON_D1); break;
            case 3: check(!NOT_MOTORON_D0 && !NOT_MOTORON_D1); break;
        }
#else
        switch(DSMAP(ds)) {
            case 0: check(!NOT_MOTORON_D0 && NOT_MOTORON_D1); break;
            case 1: check(!NOT_MOTORON_D0 && !NOT_MOTORON_D1); break;
            case 2: check(!NOT_MOTORON_D0 && !NOT_MOTORON_D1); break;
            case 3: check(!NOT_MOTORON_D0 && !NOT_MOTORON_D1); break;
        }
#endif
    }
    external_clr();
    check(NOT_MOTORON_D0 && NOT_MOTORON_D1);

    di();
    
#ifdef EEPROM
    // Check default set/init functions
    for (map = 0; map < NUM_MAPS; map++) {
        set_default_map(map);
        check(default_map == map);
        default_map = INVALID_MAP;
        init_default_map();
        check(default_map == map);
    }
#endif

    // Everything looks good, mark tests as passed.
    // Device will be enabled at the next reset.
    write_eeprom(unit_test_address, UNIT_PASS);
    set_default_map(NO_MAP);
    pass_halt();
}

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    uint8_t test_status = setup_tests();

#if defined(FORCE_M4P) || defined(FORCE_NOT_M4P)
    if (!(DEBUGGER_ATTACHED) && test_status != RUN_TESTS) {
        // disable interrupt sources ~CLR, CLK, and ENABLE
        // flip NOT_M4P to an output so we can control it.
        TRISA &= ~BIT(6);
        TRISB &= ~(BIT(0)| BIT(5) | BIT(7));
        LATB5 = 1;
#ifdef FORCE_M4P
        LATB7 = 0;
#else
        LATB7 = 1;
#endif
    }
#endif

    // Only enable m4p mode when:
    // 1) No debugger is attached
    //    (otherwise the debugger will be driving NOT_M4P)
    // 2) Unit tests aren't about to be run
    //    (will cause test failures if open drain is enabled on DS2 and DS3).
    // 3) NOT_M4P pin pulled low
    if (!(DEBUGGER_ATTACHED) && test_status != RUN_TESTS && !NOT_M4P)
        enable_m4p();

    mapper_init();

    // If a device that failed unit tests is installed, halt
    // after outputs have been initialized, but before interrupts are enabled
    // so it can do as little harm as possible.
    if (test_status == UNIT_FAIL)
        error_halt();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    if (test_status == RUN_TESTS)
        unit_tests();

#ifdef PROTO
    // Hack: set row4 so we blink RA4 on the proto board.
    di();
    set_current_map(3);
    enabled_map=3;
    ei();
#endif
#if defined(FORCE_M4P) || defined(FORCE_NOT_M4P)
    // Set the default and map to 2 so we blink some leds
    default_map=enabled_map=2;
    set_map_leds();
#endif
    
    // setup blink timer to show MCU is alive.
    TMR0_SetInterruptHandler(&row_timer);

    while (1)
    {
        // go into low power mode
        SLEEP();
    }
}
/**
 End of File
*/
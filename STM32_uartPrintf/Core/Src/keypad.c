/*
 * keypad.c
 *
 *  Created on: Mar 11, 2025
 *      Author: tomdo
 */
#include "gpio.h"


// Keypad matrix
char keys[4][4] = {
	{'*', '0', '#', 'D'},
	{'7', '8', '9', 'C'},
	{'4', '5', '6', 'B'},
    {'1', '2', '3', 'A'}

};


/*
 * This function scans a 4x4 matrix keypad and returns the character corresponding to the pressed key.
 * It works by iterating through each row, activating one row at a time (by setting it to LOW)
 * and then checking each column for a key press. When a key press is detected (when the corresponding
 * column pin is LOW), the function returns the character that corresponds to the row and column of the pressed key.
 * If no key is pressed, the function returns '-'.
 */
char key_scan(void) {
	// Define rows and columns pins and ports
    const uint16_t rows[4] = {row1_Pin, row2_Pin, row3_Pin, row4_Pin};
    const uint16_t cols[4] = {col1_Pin, col2_Pin, col3_Pin, col4_Pin};
    GPIO_TypeDef* row_ports[4] = {row1_GPIO_Port, row2_GPIO_Port, row3_GPIO_Port, row4_GPIO_Port};
    GPIO_TypeDef* col_ports[4] = {col1_GPIO_Port, col2_GPIO_Port, col3_GPIO_Port, col4_GPIO_Port};

    // Loop through each row
    for (int row = 0; row < 4; row++) {
    	// Set row to LOW (activate)
        LL_GPIO_ResetOutputPin(row_ports[row], rows[row]);

        // Check each column
        for (int col = 0; col < 4; col++) {
        	// If key is pressed (column is LOW)
            if (LL_GPIO_IsInputPinSet(col_ports[col], cols[col]) == 0) {
            	// Reset row to HIGH (deactivate)
                LL_GPIO_SetOutputPin(row_ports[row], rows[row]);
                return keys[row][col];  // Return corresponding key
            }
        }
        // Set row back to HIGH
        LL_GPIO_SetOutputPin(row_ports[row], rows[row]);  // Désactiver la ligne
    }
    // Return '-' if no key is pressed
    return '-';
}

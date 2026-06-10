#ifndef __KNIGHT_TOUR_H__
#define __KNIGHT_TOUR_H__

#define BOARD_SIZE (64)

typedef unsigned char pos_xy_t;
typedef pos_xy_t path_t[BOARD_SIZE];

/************************ KnightsTour ***********************
 * Description:   calculates the knights tour route , given the starting
 *                position, in the timeout time-limit, using Warnsdorff heuristics if enabled.
 *                knight's path is written into dest_path upon success.
 *
 * Arguments:     start_pos - the start position of the knight in the board.
 *                            must be a valid position.
 *                dest_path - a valid pointer to insert the path of the knight
 *                            for a successful tour.
 *                timeout - the maximum amount of seconds for the function
 *                          to look the a valid tour.
 *                use_heuristic - 1 to use warnsdorff heuristics in the
 *                                tour calculation. or 0 to use plain back-tracking.
 *
 * Return:        0 upon success, non-zero upon failure.
 *
 * Complexity:    time: O(BOARD_SIZE^n) for plain back-tracking
 *                      O(~n) for warnsdorff heuristic ,
 *                space: O(n)
 ****************************************************************/
int KnightsTour(pos_xy_t start_pos, path_t dest_path, unsigned int timeout, int use_heuristic);

/************************ IsValidPosition ************************
 * Description:   tells whether the provided position is valid or not
 *
 * Arguments:     pos - the position to check
 *
 * Return:        non-zero if its valid, 0 if not
 *
 * Complexity:    time: O(1) , space: O(1)
 *****************************************************************/
int IsValidPosition(pos_xy_t pos);

/************************* BuildingPosition **********************
 * Description: The function converts X-Y coordinants to a position on th board
 *              of type pos_xy_t.
 *
 *
 *   Arguments: x - the x coordinate of the position as a numeric char
 *                  value(range(range 0-7).
 *              y - the y coordinate of the position as a numeric char
 *                  value(range(range 0-7).
 *
 *      Return: a type pos_xy_t type position.
 *
 *  Complexity: Time: O(1) Space: O(1)
*******************************************************************/
pos_xy_t BuildPosition(unsigned char x, unsigned char y);

/************************* ParsePosition **************************************
*         
* Description: Parses a position of type pos_xy_t to unsigned char coordinate
*                
*   Arguments: pos - pos_xy_t type that was returned from BuildPosition
*               or KnightsTour (in form of path_t)
*              x   - output parameter for the x value of the cordinate
*              y   - output parameter for the y value of the cordinate
*        
*      Return: None. Out params x, y
*        
*  Complexity: Time: O(1) Space: O(1)
*        
*        
******************************************************************************/
void ParsePosition(pos_xy_t pos, unsigned char *x, unsigned char *y);

#endif /* End of __KNIGHT_TOUR_H__ */
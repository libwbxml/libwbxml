/*
 * Leaktrack, a Memory Leack Tracker.
 * Copyright (C) 2002-2008 Aymerick Jehanne <aymerick@jehanne.org>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *  
 * GPL v2: http://www.gnu.org/licenses/gpl.txt
 * 
 * Contact: aymerick@jehanne.org
 * Home: http://libwbxml.aymerick.com
 */

/** 
 * @file lt_log.h
 * @ingroup leaktrack
 *
 * @brief Log Functions
 *
 * @note Code adapted from Kannel project (http://www.kannel.org/)
 */

#ifndef LEAKTRACK_LOG_H
#define LEAKTRACK_LOG_H

/**
 * @brief Open the log file
 * @param filename The logfile name
 */
LT_DECLARE(void) lt_log_open_file(char *filename);

/**
 * @brief Logging function
 * @param e If different from 0, try to resolve a system error
 * @param fmt The log text (in printf style)
 */
LT_DECLARE_NONSTD(void) lt_log(int e, const char *fmt, ...);

/**
 * @brief Close the log file
 */
LT_DECLARE(void) lt_log_close_file(void);

#endif
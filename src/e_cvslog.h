/*
 * e_cvslog.h
 *
 * Copyright (c) 2008, eFTE SF Group (see AUTHORS file)
 *
 * You may distribute under the terms of either the GNU General Public
 * License or the Artistic License, as specified in the README file.
 *
 * Contributed by Martin Frydl <frydl@matfyz.cz>
 *
 * Subclass of EBuffer for writing log for CVS commit. Creates temporary file
 * used for commit which is deleted when view is closed. Asks for commit or
 * discard on view close.
 */

#ifndef _CVSLOG_H_
#define _CVSLOG_H_

#include "e_buffer.h"

class ECvsLog: public EBuffer {
public:
    ECvsLog(int createFlags, EModel **ARoot, const char *Directory, const char *OnFiles);
    ~ECvsLog();

    // List files into buffer
    // p        - line where to print
    // fCount   - number of files which will be printed
    // title    - title
    // cnt      - total number of files
    // position - positions of files in list
    // len      - length of files
    // status   - status of files
    // list     - list of filenames
    // incexc   - status of files to print/not to print
    // exc      - incexc is exclusion
    void ListFiles(int &p, const int fCount, const char *title, const int cnt, const int *position, const int *len, const char *status, const char *list, const char *excinc, const int exc = 0);

    virtual int CanQuit() const;
    virtual int ConfQuit(GxView *V, int multiFile = 0);
    virtual EViewPort *CreateViewPort(EView *V);

    virtual void GetName(char *AName, int MaxLen) const;
    virtual void GetInfo(char *AInfo, int MaxLen) const;
    virtual void GetTitle(char *ATitle, int MaxLen, char *ASTitle, int SMaxLen) const;
};

extern ECvsLog *CvsLogView;

#endif

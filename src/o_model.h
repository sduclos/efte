/*    o_model.h
 *
 *    Copyright (c) 2008, eFTE SF Group (see AUTHORS file)
 *    Copyright (c) 1994-1996, Marko Macek
 *
 *    You may distribute under the terms of either the GNU General Public
 *    License or the Artistic License, as specified in the README file.
 *
 */

#ifndef O_MODEL_H
#define O_MODEL_H

#include "console.h" // TEvent

class EView;
class EEventMap;
class ExState;
class ExModelView;
class GxView;

class EViewPort {
public:
    EView *View;
    int ReCenter;

    EViewPort(EView *V);
    virtual ~EViewPort();

    virtual void HandleEvent(TEvent &Event);
    virtual void UpdateView();
    virtual void RepaintView();
    virtual void UpdateStatus();
    virtual void RepaintStatus();

    virtual void GetPos();
    virtual void StorePos();

    virtual void Resize(int Width, int Height);
};

enum createFlags {
    cfAppend = 1,
    cfNoActivate = 2
};

class EModel {
public:
    EModel **Root;   // root ptr of this list
    EModel *Next;    // next model
    EModel *Prev;    // prev model
    EView *View;     // active view of model

    int ModelNo;

    EModel(int createFlags, EModel **ARoot);
    virtual ~EModel();

    void AddView(EView *V);
    void RemoveView(EView *V);
    void SelectView(EView *V);

    virtual EViewPort *CreateViewPort(EView *V);

    virtual int GetContext() const;
    virtual EEventMap *GetEventMap();
    virtual int BeginMacro();
    virtual int ExecCommand(int Command, ExState &State);
    virtual void HandleEvent(TEvent &Event);

    virtual void GetName(char *AName, int MaxLen) const;
    virtual void GetPath(char *APath, int MaxLen) const;
    virtual void GetInfo(char *AInfo, int MaxLen) const;
    virtual void GetTitle(char *ATitle, int MaxLen,
                          char *ASTitle, int SMaxLen) const;

    void UpdateTitle();

    void Msg(int level, const char *s, ...);
    virtual int CanQuit() const;
    virtual int ConfQuit(GxView *V, int multiFile = 0);

    virtual int GetStrVar(int var, char *str, int buflen);
    virtual int GetIntVar(int var, int *value);

    virtual void NotifyPipe(int PipeId);

    virtual void NotifyDelete(EModel *Deleting);
    virtual void DeleteRelated();
};

class EView {
public:
    EView *Next;        // next view
    EView *Prev;        // prev view
    ExModelView *MView; // model view controller
    EModel *Model;       // model for this view
    EView *NextView;    // next view for model
    EViewPort *Port;
    char *CurMsg;

    EView(EModel *AModel);
    virtual ~EView();

    virtual void FocusChange(int GotFocus);
    virtual void Resize(int Width, int Height);

    void SetModel(EModel *AModel);
    void SelectModel(EModel *AModel);
    void SwitchToModel(EModel *AModel);

    void Activate(int GotFocus);

    virtual int GetContext() const;
    virtual EEventMap *GetEventMap();
    virtual int BeginMacro();
    virtual int ExecCommand(int Command, ExState &State);

    virtual void HandleEvent(TEvent &Event);
    virtual void UpdateView();
    virtual void RepaintView();
    virtual void UpdateStatus();
    virtual void RepaintStatus();

    void Msg(int level, const char *s, ...);
    void SetMsg(const char *msg);

    int SwitchTo(ExState &State);
    int FilePrev();
    int FileNext();
    int FileLast();
    int FileSaveAll();
    int FileOpen(ExState &State);
    int FileOpenInMode(ExState &State);
    int SetPrintDevice(ExState &State);
    int ToggleSysClipboard(ExState &State);
    int ShowKey(ExState &State);
    int ViewBuffers(ExState &State);
    int ViewRoutines(ExState &State);
    int Compile(ExState &State);
    int RunCompiler(ExState &State);
    int Compile(const char *Command);
    int ViewMessages(ExState &State);
    int CompilePrevError(ExState &State);
    int CompileNextError(ExState &State);
    int ConfigRecompile(ExState &State);
    int Cvs(ExState &State);
    int RunCvs(ExState &State);
    int ViewCvs(ExState &State);
    int Cvs(const char *Options);
    int ClearCvsMessages(ExState &State);
    int CvsDiff(ExState &State);
    int RunCvsDiff(ExState &State);
    int ViewCvsDiff(ExState &State);
    int CvsDiff(const char *Options);
    int CvsCommit(ExState &State);
    int RunCvsCommit(ExState &State);
    int CvsCommit(const char *Options);
    int ViewCvsLog(ExState &State);
    int Svn(ExState &State);
    int RunSvn(ExState &State);
    int ViewSvn(ExState &State);
    int Svn(const char *Options);
    int ClearSvnMessages(ExState &State);
    int SvnDiff(ExState &State);
    int RunSvnDiff(ExState &State);
    int ViewSvnDiff(ExState &State);
    int SvnDiff(const char *Options);
    int SvnCommit(ExState &State);
    int RunSvnCommit(ExState &State);
    int SvnCommit(const char *Options);
    int ViewSvnLog(ExState &State);
    int DirOpen(ExState &State);
    int OpenDir(const char *Directory);
    int ShowVersion();
    int ViewModeMap(ExState &State);
    int ClearMessages();
    int TagLoad(ExState &State);
    int SysShowHelp(ExState &State, const char *word);

    int RemoveGlobalBookmark(ExState &State);
    int GotoGlobalBookmark(ExState &State);
    int PopGlobalBookmark();

    void DeleteModel(EModel *M);
    int CanQuit() const;

    int GetStrVar(int var, char *str, int buflen);
    int GetIntVar(int var, int *value);
};

extern EModel *ActiveModel;
extern EView *ActiveView;

int GetNewModelID(EModel *B);
EModel *FindModelID(EModel *B, int ID);

#define MSGBUFTMP_SIZE 1024

#endif // O_MODEL_H

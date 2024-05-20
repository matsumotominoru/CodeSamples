VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   4590
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   5910
   LinkTopic       =   "Form1"
   ScaleHeight     =   4590
   ScaleWidth      =   5910
   StartUpPosition =   3  'Windows ÇÃä˘íËíl
   Begin VB.ListBox lstItems 
      Height          =   2220
      Left            =   120
      TabIndex        =   11
      Top             =   2160
      Width           =   5655
   End
   Begin VB.TextBox txtItem 
      Height          =   405
      Left            =   120
      TabIndex        =   10
      Top             =   1560
      Width           =   5655
   End
   Begin VB.CommandButton cmdAddDev 
      Caption         =   "Add Developer"
      Height          =   492
      Left            =   4440
      TabIndex        =   3
      Top             =   120
      Width           =   1335
   End
   Begin VB.CommandButton cmdAddSec 
      Caption         =   "New Secretary"
      Height          =   492
      Left            =   3000
      TabIndex        =   2
      Top             =   120
      Width           =   1335
   End
   Begin VB.CommandButton cmdAddMgr 
      Caption         =   "New Manager"
      Height          =   492
      Left            =   1560
      TabIndex        =   1
      Top             =   120
      Width           =   1335
   End
   Begin VB.CommandButton cmdShow 
      Caption         =   "Show"
      Height          =   492
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1335
   End
   Begin VB.Label Label6 
      Caption         =   "Number of Developers"
      Height          =   255
      Left            =   3240
      TabIndex        =   9
      Top             =   720
      Width           =   1815
   End
   Begin VB.Label Label5 
      Caption         =   "Secretary"
      Height          =   255
      Left            =   120
      TabIndex        =   8
      Top             =   1080
      Width           =   855
   End
   Begin VB.Label Label4 
      Caption         =   "Manager"
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   720
      Width           =   855
   End
   Begin VB.Label lblCount 
      BorderStyle     =   1  'é¿ê¸
      Height          =   375
      Left            =   5040
      TabIndex        =   6
      Top             =   720
      Width           =   735
   End
   Begin VB.Label lblSec 
      BorderStyle     =   1  'é¿ê¸
      Height          =   375
      Left            =   1080
      TabIndex        =   5
      Top             =   1080
      Width           =   1815
   End
   Begin VB.Label lblMgr 
      BorderStyle     =   1  'é¿ê¸
      Height          =   375
      Left            =   1080
      TabIndex        =   4
      Top             =   720
      Width           =   1815
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim bu As BusinessUnit
Dim id As Long

Private Sub cmdAddDev_Click()
   If txtItem = "" Then Exit Sub
   Dim emp As New Employee
   id = id + 1
   emp.Name = txtItem
   emp.EmployeeID = id
   bu.Developers.Add emp
   lblCount = Str$(bu.Developers.Count)
   txtItem = ""
End Sub

Private Sub cmdAddMgr_Click()
   If txtItem = "" Then Exit Sub
   Dim emp As New Employee
   id = id + 1
   emp.Name = txtItem
   emp.EmployeeID = id
   bu.Manager = emp
   lblMgr = bu.Manager.Name
   txtItem = ""
End Sub

Private Sub cmdAddSec_Click()
   If txtItem = "" Then Exit Sub
   Dim emp As New Employee
   id = id + 1
   emp.Name = txtItem
   emp.EmployeeID = id
   bu.Secretary = emp
   lblSec = bu.Secretary.Name
   txtItem = ""
End Sub

Private Sub cmdShow_Click()
   lblCount = Str$(bu.Developers.Count)
   lblMgr = bu.Manager.Name
   lblSec = bu.Secretary.Name

   lstItems.Clear
   lstItems.AddItem "Manager: " + bu.Manager.Name _
      + ", " + Str$(bu.Manager.EmployeeID)
   lstItems.AddItem "Secretary: " + bu.Secretary.Name _
      + ", " + Str$(bu.Secretary.EmployeeID)
   lstItems.AddItem "Developers:"
   If bu.Developers.Count = 0 Then
      lstItems.AddItem "  No developers"
      Exit Sub
   End If

   Dim emp As Employee
   For Each emp In bu.Developers
    lstItems.AddItem "  " + emp.Name + ", " + Str$(emp.EmployeeID)
   Next
End Sub

Private Sub Form_Load()
   Set bu = New BusinessUnit
   id = 0
   lblCount = Str$(bu.Developers.Count)
   lblMgr = bu.Manager.Name
   lblSec = bu.Secretary.Name
End Sub

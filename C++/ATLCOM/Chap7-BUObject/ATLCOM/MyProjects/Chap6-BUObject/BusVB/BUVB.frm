VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Developers Collection"
   ClientHeight    =   4665
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4035
   LinkTopic       =   "Form1"
   ScaleHeight     =   4665
   ScaleWidth      =   4035
   StartUpPosition =   3  'Windows ÇÃä˘íËíl
   Begin VB.ListBox lstItems 
      Height          =   2400
      Left            =   240
      TabIndex        =   5
      Top             =   2040
      Width           =   3495
   End
   Begin VB.TextBox txtItem 
      Height          =   375
      Left            =   240
      TabIndex        =   2
      Top             =   960
      Width           =   3495
   End
   Begin VB.CommandButton cmdAdd 
      Caption         =   "Add"
      Height          =   615
      Left            =   2400
      TabIndex        =   1
      Top             =   120
      Width           =   1335
   End
   Begin VB.CommandButton cmdShow 
      Caption         =   "Show"
      Height          =   615
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   1335
   End
   Begin VB.Label lblCount 
      BorderStyle     =   1  'é¿ê¸
      Height          =   375
      Left            =   1920
      TabIndex        =   4
      Top             =   1440
      Width           =   1815
   End
   Begin VB.Label Label1 
      Caption         =   "Number of Items"
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   1440
      Width           =   1455
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim Devs As DeveloperCollection
Dim id As Long
Private Sub cmdAdd_Click()
   If txtItem = "" Then Exit Sub
   Dim Emp As New Employee
   id = id + 1
   Emp.Name = txtItem
   Emp.EmployeeID = id
   Devs.Add Emp
   lblCount = Str$(Devs.Count)
   txtItem = ""
End Sub

Private Sub cmdShow_Click()
   lstItems.Clear
   For Each Emp In Devs
      lstItems.AddItem Emp.Name & ", " & Str$(Emp.EmployeeID)
   Next
End Sub

Private Sub Form_Load()
   Set Devs = New DeveloperCollection
   id = 0
End Sub

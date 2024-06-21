    ; ************************************
    ; console mode text input and output *
    ; ************************************
    print MACRO arg1:REQ,varname:VARARG      ;; display zero terminated string
        IFNDEF __UNICODE__
          invoke StdOut,expand_prefix(reparg(arg1))
        ELSE
          invoke StdOutW,expand_prefix(reparg(arg1))
        ENDIF
      IFNB <varname>
        IFNDEF __UNICODE__
          invoke StdOut,chr$(varname)
        ELSE
          invoke StdOutW,chr$(varname)
        ENDIF
      ENDIF
    ENDM

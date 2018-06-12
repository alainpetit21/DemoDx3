<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: Demo - Win32 (WCE MIPS) Release--------------------
</h3>
<h3>Command Lines</h3>
Creating temporary file "C:\WINDOWS\TEMP\RSPF2E0.TMP" with contents
[
/nologo /W3 /D "_DEBUG" /D _WIN32_WCE=300 /D "WIN32_PLATFORM_PSPC" /D "MIPS" /D "_MIPS_" /D UNDER_CE=300 /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /D "_PROFILE" /D "_POCKET_PC" /Fp"MIPSRel/Demo.pch" /YX /Fo"MIPSRel/" /Oxs /MC /c 
"C:\projects\Demo\toto3.cpp"
]
Creating command line "clmips.exe @C:\WINDOWS\TEMP\RSPF2E0.TMP" 
Creating temporary file "C:\WINDOWS\TEMP\RSPF2E1.TMP" with contents
[
coredll.lib gx.lib /nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"WinMainCRTStartup" /incremental:no /pdb:"MIPSRel/Demo.pdb" /nodefaultlib:"libc.lib /nodefaultlib:libcd.lib /nodefaultlib:libcmt.lib /nodefaultlib:libcmtd.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib /nodefaultlib:oldnames.lib" /out:"MIPSRel/Demo.exe" /subsystem:windowsce,3.00 /MACHINE:MIPS 
.\MIPSRel\3DDisplay.obj
.\MIPSRel\audio.obj
.\MIPSRel\file.obj
.\MIPSRel\graphic.obj
.\MIPSRel\input.obj
.\MIPSRel\mathFP.obj
.\MIPSRel\resman.obj
.\MIPSRel\sys.obj
.\MIPSRel\toto3.obj
]
Creating command line "link.exe @C:\WINDOWS\TEMP\RSPF2E1.TMP"
<h3>Output Window</h3>
Compiling...
toto3.cpp
Linking...



<h3>Results</h3>
Demo.exe - 0 error(s), 0 warning(s)
</pre>
</body>
</html>

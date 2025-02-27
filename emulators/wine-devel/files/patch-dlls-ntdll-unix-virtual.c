commit 59da79021a6e441e3b21b933c744aba922208ec1
Author: Gerald Pfeifer <gerald@pfeifer.com>
Date:   Tue Aug 10 22:36:27 2021 +0200

    ntdll: Only use sysinfo function when present.
    
    On some systems <sys/sysinfo.h> may be present while the sysinfo
    function may not, or at least not as part of standard libraries,
    so check whether the function is actually available before using
    it.
    
    This fixes builds on FreeBSD with the devel/libsysinfo present.
    
    Signed-off-by: Gerald Pfeifer <gerald@pfeifer.com>
    Signed-off-by: Alexandre Julliard <julliard@winehq.org>

diff --git a/configure b/configure
index 1be0aa9d217..e8c1cb9e3a8 100755
--- configure
+++ configure
@@ -18068,6 +18068,7 @@ for ac_func in \
 	setprogname \
 	sigprocmask \
 	symlink \
+	sysinfo \
 	tcdrain \
 	thr_kill2
 
diff --git a/configure.ac b/configure.ac
index 69e27147088..065b3f231bf 100644
--- configure.ac
+++ configure.ac
@@ -2205,6 +2205,7 @@ AC_CHECK_FUNCS(\
 	setprogname \
 	sigprocmask \
 	symlink \
+	sysinfo \
 	tcdrain \
 	thr_kill2
 )
diff --git a/dlls/ntdll/unix/virtual.c b/dlls/ntdll/unix/virtual.c
index a252e25fbc6..2cca90ac952 100644
--- dlls/ntdll/unix/virtual.c
+++ dlls/ntdll/unix/virtual.c
@@ -2737,7 +2737,8 @@ ULONG_PTR get_system_affinity_mask(void)
  */
 void virtual_get_system_info( SYSTEM_BASIC_INFORMATION *info, BOOL wow64 )
 {
-#if defined(HAVE_STRUCT_SYSINFO_TOTALRAM) && defined(HAVE_STRUCT_SYSINFO_MEM_UNIT)
+#if defined(HAVE_SYSINFO) \
+    && defined(HAVE_STRUCT_SYSINFO_TOTALRAM) && defined(HAVE_STRUCT_SYSINFO_MEM_UNIT)
     struct sysinfo sinfo;
 
     if (!sysinfo(&sinfo))
diff --git a/include/config.h.in b/include/config.h.in
index ad770281471..24f7b64ffd3 100644
--- include/config.h.in
+++ include/config.h.in
@@ -744,6 +744,9 @@
 /* Define to 1 if you have the <syscall.h> header file. */
 #undef HAVE_SYSCALL_H
 
+/* Define to 1 if you have the `sysinfo' function. */
+#undef HAVE_SYSINFO
+
 /* Define to 1 if you have the
    <SystemConfiguration/SCDynamicStoreCopyDHCPInfo.h> header file. */
 #undef HAVE_SYSTEMCONFIGURATION_SCDYNAMICSTORECOPYDHCPINFO_H

# Makefile for PO directory in any package using GNU gettext.
# Copyright (C) 1995-1997, 2000-2007, 2009-2010 by Ulrich Drepper <drepper@gnu.ai.mit.edu>
#
# This file can be copied and used freely without restrictions.  It can
# be used in projects which are not available under the GNU General Public
# License but which still want to provide support for the GNU gettext
# functionality.
# Please note that the actual code of GNU gettext is covered by the GNU
# General Public License and is *not* in the public domain.
#
# Origin: gettext-0.19
GETTEXT_MACRO_VERSION = 0.19

PACKAGE = sharutils
VERSION = 4.15
PACKAGE_BUGREPORT = bug-gnu-utils@gnu.org

SED = /bin/sed
SHELL = /bin/sh


srcdir = ../../po
top_srcdir = ../..
VPATH = ../../po

prefix = /usr/local
exec_prefix = ${prefix}
datarootdir = ${prefix}/share
datadir = ${datarootdir}
localedir = ${datarootdir}/locale
gettextsrcdir = $(datadir)/gettext/po

INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644

# We use $(mkdir_p).
# In automake <= 1.9.x, $(mkdir_p) is defined either as "mkdir -p --" or as
# "$(mkinstalldirs)" or as "$(install_sh) -d". For these automake versions,
# ${SHELL} /home/min/a/cgusthin/git/klee/benchmarks/klee-array-bench/case_studies/sharutils/sharutils-4.15/install-sh does not start with $(SHELL), so we add it.
# In automake >= 1.10, $(MKDIR_P) is derived from ${MKDIR_P}, which is defined
# either as "/path/to/mkdir -p" or ".../install-sh -c -d". For these automake
# versions, $(mkinstalldirs) and $(install_sh) are unused.
mkinstalldirs = $(SHELL) ${SHELL} /home/min/a/cgusthin/git/klee/benchmarks/klee-array-bench/case_studies/sharutils/sharutils-4.15/install-sh -d
install_sh = $(SHELL) ${SHELL} /home/min/a/cgusthin/git/klee/benchmarks/klee-array-bench/case_studies/sharutils/sharutils-4.15/install-sh
MKDIR_P = /bin/mkdir -p
mkdir_p = $(MKDIR_P)

GMSGFMT_ = /usr/bin/msgfmt
GMSGFMT_no = /usr/bin/msgfmt
GMSGFMT_yes = /usr/bin/msgfmt
GMSGFMT = $(GMSGFMT_$(USE_MSGCTXT))
MSGFMT_ = /usr/bin/msgfmt
MSGFMT_no = /usr/bin/msgfmt
MSGFMT_yes = /usr/bin/msgfmt
MSGFMT = $(MSGFMT_$(USE_MSGCTXT))
XGETTEXT_ = /usr/bin/xgettext
XGETTEXT_no = /usr/bin/xgettext
XGETTEXT_yes = /usr/bin/xgettext
XGETTEXT = $(XGETTEXT_$(USE_MSGCTXT))
MSGMERGE = msgmerge
MSGMERGE_UPDATE = /usr/bin/msgmerge --update
MSGINIT = msginit
MSGCONV = msgconv
MSGFILTER = msgfilter

POFILES =  $(srcdir)/bg.po $(srcdir)/ca.po $(srcdir)/cs.po $(srcdir)/da.po $(srcdir)/de.po $(srcdir)/el.po $(srcdir)/eo.po $(srcdir)/es.po $(srcdir)/et.po $(srcdir)/fi.po $(srcdir)/fr.po $(srcdir)/ga.po $(srcdir)/gl.po $(srcdir)/hu.po $(srcdir)/id.po $(srcdir)/it.po $(srcdir)/ja.po $(srcdir)/nl.po $(srcdir)/pl.po $(srcdir)/pt_BR.po $(srcdir)/ru.po $(srcdir)/sr.po $(srcdir)/sv.po $(srcdir)/tr.po $(srcdir)/uk.po $(srcdir)/vi.po $(srcdir)/zh_CN.po $(srcdir)/zh_TW.po
GMOFILES =  $(srcdir)/bg.gmo $(srcdir)/ca.gmo $(srcdir)/cs.gmo $(srcdir)/da.gmo $(srcdir)/de.gmo $(srcdir)/el.gmo $(srcdir)/eo.gmo $(srcdir)/es.gmo $(srcdir)/et.gmo $(srcdir)/fi.gmo $(srcdir)/fr.gmo $(srcdir)/ga.gmo $(srcdir)/gl.gmo $(srcdir)/hu.gmo $(srcdir)/id.gmo $(srcdir)/it.gmo $(srcdir)/ja.gmo $(srcdir)/nl.gmo $(srcdir)/pl.gmo $(srcdir)/pt_BR.gmo $(srcdir)/ru.gmo $(srcdir)/sr.gmo $(srcdir)/sv.gmo $(srcdir)/tr.gmo $(srcdir)/uk.gmo $(srcdir)/vi.gmo $(srcdir)/zh_CN.gmo $(srcdir)/zh_TW.gmo
UPDATEPOFILES =  bg.po-update ca.po-update cs.po-update da.po-update de.po-update el.po-update eo.po-update es.po-update et.po-update fi.po-update fr.po-update ga.po-update gl.po-update hu.po-update id.po-update it.po-update ja.po-update nl.po-update pl.po-update pt_BR.po-update ru.po-update sr.po-update sv.po-update tr.po-update uk.po-update vi.po-update zh_CN.po-update zh_TW.po-update
DUMMYPOFILES =  bg.nop ca.nop cs.nop da.nop de.nop el.nop eo.nop es.nop et.nop fi.nop fr.nop ga.nop gl.nop hu.nop id.nop it.nop ja.nop nl.nop pl.nop pt_BR.nop ru.nop sr.nop sv.nop tr.nop uk.nop vi.nop zh_CN.nop zh_TW.nop
DISTFILES.common = Makefile.in.in remove-potcdate.sin \
$(DISTFILES.common.extra1) $(DISTFILES.common.extra2) $(DISTFILES.common.extra3)
DISTFILES = $(DISTFILES.common) Makevars POTFILES.in \
$(POFILES) $(GMOFILES) \
$(DISTFILES.extra1) $(DISTFILES.extra2) $(DISTFILES.extra3)

POTFILES = \
     ../../src/encode.c \
     ../../src/local.h \
     ../../src/scribble.c \
     ../../src/scribble.h \
     ../../src/scripts.x \
     ../../src/shar-opts.c \
     ../../src/shar-opts.h \
     ../../src/shar.c \
     ../../src/unshar-opts.c \
     ../../src/unshar-opts.h \
     ../../src/unshar.c \
     ../../src/uudecode-opts.c \
     ../../src/uudecode-opts.h \
     ../../src/uudecode.c \
     ../../src/uuencode-opts.c \
     ../../src/uuencode-opts.h \
     ../../src/uuencode.c \
     ../../lib/alloca.c \
     ../../lib/alloca.in.h \
     ../../lib/anytostr.c \
     ../../lib/assure.h \
     ../../lib/at-func.c \
     ../../lib/base64.c \
     ../../lib/base64.h \
     ../../lib/basename-lgpl.c \
     ../../lib/basename.c \
     ../../lib/binary-io.c \
     ../../lib/binary-io.h \
     ../../lib/c-ctype.c \
     ../../lib/c-ctype.h \
     ../../lib/c-strcase.h \
     ../../lib/c-strcasecmp.c \
     ../../lib/c-strcaseeq.h \
     ../../lib/c-strncasecmp.c \
     ../../lib/chdir-long.c \
     ../../lib/chdir-long.h \
     ../../lib/cloexec.c \
     ../../lib/cloexec.h \
     ../../lib/close.c \
     ../../lib/closedir.c \
     ../../lib/ctype.in.h \
     ../../lib/dirent-private.h \
     ../../lib/dirent.in.h \
     ../../lib/dirfd.c \
     ../../lib/dirname-lgpl.c \
     ../../lib/dirname.c \
     ../../lib/dirname.h \
     ../../lib/dosname.h \
     ../../lib/dup-safer-flag.c \
     ../../lib/dup-safer.c \
     ../../lib/dup.c \
     ../../lib/dup2.c \
     ../../lib/errno.in.h \
     ../../lib/error.c \
     ../../lib/error.h \
     ../../lib/exitfail.c \
     ../../lib/exitfail.h \
     ../../lib/fatal-signal.c \
     ../../lib/fatal-signal.h \
     ../../lib/fchdir.c \
     ../../lib/fcntl.c \
     ../../lib/fcntl.in.h \
     ../../lib/fd-hook.c \
     ../../lib/fd-hook.h \
     ../../lib/fd-safer-flag.c \
     ../../lib/fd-safer.c \
     ../../lib/fdopendir.c \
     ../../lib/fflush.c \
     ../../lib/filename.h \
     ../../lib/filenamecat-lgpl.c \
     ../../lib/filenamecat.h \
     ../../lib/fpurge.c \
     ../../lib/freading.c \
     ../../lib/freading.h \
     ../../lib/freopen.c \
     ../../lib/fseek.c \
     ../../lib/fseeko.c \
     ../../lib/fstat.c \
     ../../lib/fstatat.c \
     ../../lib/ftell.c \
     ../../lib/ftello.c \
     ../../lib/getcwd-lgpl.c \
     ../../lib/getcwd.c \
     ../../lib/getdtablesize.c \
     ../../lib/gethostname.c \
     ../../lib/getopt.c \
     ../../lib/getopt.in.h \
     ../../lib/getopt1.c \
     ../../lib/getopt_int.h \
     ../../lib/gettext.h \
     ../../lib/gettimeofday.c \
     ../../lib/gl_openssl.h \
     ../../lib/idcache.c \
     ../../lib/idcache.h \
     ../../lib/imaxtostr.c \
     ../../lib/intprops.h \
     ../../lib/inttostr.c \
     ../../lib/inttostr.h \
     ../../lib/inttypes.in.h \
     ../../lib/liballoca.h \
     ../../lib/localcharset.c \
     ../../lib/localcharset.h \
     ../../lib/lseek.c \
     ../../lib/lstat.c \
     ../../lib/malloc.c \
     ../../lib/mbrtowc.c \
     ../../lib/mbsinit.c \
     ../../lib/md5.c \
     ../../lib/md5.h \
     ../../lib/memchr.c \
     ../../lib/mempcpy.c \
     ../../lib/memrchr.c \
     ../../lib/mkstemp.c \
     ../../lib/mktime-internal.h \
     ../../lib/mktime.c \
     ../../lib/msvc-inval.c \
     ../../lib/msvc-inval.h \
     ../../lib/msvc-nothrow.c \
     ../../lib/msvc-nothrow.h \
     ../../lib/offtostr.c \
     ../../lib/open.c \
     ../../lib/openat-die.c \
     ../../lib/openat-priv.h \
     ../../lib/openat-proc.c \
     ../../lib/openat.c \
     ../../lib/openat.h \
     ../../lib/opendir.c \
     ../../lib/pathmax.h \
     ../../lib/pipe-safer.c \
     ../../lib/pipe.h \
     ../../lib/pipe2-safer.c \
     ../../lib/pipe2.c \
     ../../lib/popen.c \
     ../../lib/quote.h \
     ../../lib/quotearg.c \
     ../../lib/quotearg.h \
     ../../lib/raise.c \
     ../../lib/rawmemchr.c \
     ../../lib/readdir.c \
     ../../lib/realloc.c \
     ../../lib/rewinddir.c \
     ../../lib/save-cwd.c \
     ../../lib/save-cwd.h \
     ../../lib/sched.in.h \
     ../../lib/secure_getenv.c \
     ../../lib/sig-handler.c \
     ../../lib/sig-handler.h \
     ../../lib/sigaction.c \
     ../../lib/signal.in.h \
     ../../lib/sigprocmask.c \
     ../../lib/sockets.c \
     ../../lib/sockets.h \
     ../../lib/spawn-pipe.c \
     ../../lib/spawn-pipe.h \
     ../../lib/spawn.in.h \
     ../../lib/spawn_faction_addclose.c \
     ../../lib/spawn_faction_adddup2.c \
     ../../lib/spawn_faction_addopen.c \
     ../../lib/spawn_faction_destroy.c \
     ../../lib/spawn_faction_init.c \
     ../../lib/spawn_int.h \
     ../../lib/spawnattr_destroy.c \
     ../../lib/spawnattr_init.c \
     ../../lib/spawnattr_setflags.c \
     ../../lib/spawnattr_setsigmask.c \
     ../../lib/spawni.c \
     ../../lib/spawnp.c \
     ../../lib/stat.c \
     ../../lib/stdalign.in.h \
     ../../lib/stdbool.in.h \
     ../../lib/stddef.in.h \
     ../../lib/stdint.in.h \
     ../../lib/stdio-impl.h \
     ../../lib/stdio.in.h \
     ../../lib/stdlib.in.h \
     ../../lib/stdnoreturn.in.h \
     ../../lib/stpcpy.c \
     ../../lib/strchrnul.c \
     ../../lib/strdup.c \
     ../../lib/streq.h \
     ../../lib/strerror-override.c \
     ../../lib/strerror-override.h \
     ../../lib/strerror.c \
     ../../lib/strftime.c \
     ../../lib/strftime.h \
     ../../lib/string.in.h \
     ../../lib/stripslash.c \
     ../../lib/strndup.c \
     ../../lib/strnlen.c \
     ../../lib/strtoimax.c \
     ../../lib/strtol.c \
     ../../lib/strtoll.c \
     ../../lib/sys_socket.c \
     ../../lib/sys_socket.in.h \
     ../../lib/sys_stat.in.h \
     ../../lib/sys_time.in.h \
     ../../lib/sys_types.in.h \
     ../../lib/sys_uio.in.h \
     ../../lib/sys_utsname.in.h \
     ../../lib/sys_wait.in.h \
     ../../lib/system.h \
     ../../lib/tempname.c \
     ../../lib/tempname.h \
     ../../lib/time.in.h \
     ../../lib/time_r.c \
     ../../lib/uinttostr.c \
     ../../lib/umaxtostr.c \
     ../../lib/uname.c \
     ../../lib/unistd--.h \
     ../../lib/unistd-safer.h \
     ../../lib/unistd.c \
     ../../lib/unistd.in.h \
     ../../lib/unlocked-io.h \
     ../../lib/verify.h \
     ../../lib/w32sock.h \
     ../../lib/w32spawn.h \
     ../../lib/wait-process.c \
     ../../lib/wait-process.h \
     ../../lib/waitpid.c \
     ../../lib/wchar.in.h \
     ../../lib/wctype-h.c \
     ../../lib/wctype.in.h \
     ../../lib/xalloc-die.c \
     ../../lib/xalloc-oversized.h \
     ../../lib/xalloc.h \
     ../../lib/xgetcwd.c \
     ../../lib/xgetcwd.h \
     ../../lib/xmalloc.c \
     ../../lib/xstrndup.c \
     ../../lib/xstrndup.h \
     ../../lib/xstrtoimax.c \
     ../../lib/xstrtol-error.c \
     ../../lib/xstrtol.c \
     ../../lib/xstrtol.h \
     ../../lib/xstrtoul.c

CATALOGS =  bg.gmo ca.gmo cs.gmo da.gmo de.gmo el.gmo eo.gmo es.gmo et.gmo fi.gmo fr.gmo ga.gmo gl.gmo hu.gmo id.gmo it.gmo ja.gmo nl.gmo pl.gmo pt_BR.gmo ru.gmo sr.gmo sv.gmo tr.gmo uk.gmo vi.gmo zh_CN.gmo zh_TW.gmo

POFILESDEPS_ = $(srcdir)/$(DOMAIN).pot
POFILESDEPS_yes = $(POFILESDEPS_)
POFILESDEPS_no =
POFILESDEPS = $(POFILESDEPS_$(PO_DEPENDS_ON_POT))

DISTFILESDEPS_ = update-po
DISTFILESDEPS_yes = $(DISTFILESDEPS_)
DISTFILESDEPS_no =
DISTFILESDEPS = $(DISTFILESDEPS_$(DIST_DEPENDS_ON_UPDATE_PO))

# Makevars gets inserted here. (Don't remove this line!)
# Makefile variables -*- Mode: Makefile -*-

DOMAIN = $(PACKAGE)
subdir = po
top_builddir = ..
XGETTEXT_OPTIONS = --keyword=_ --keyword=N_ --no-wrap
COPYRIGHT_HOLDER = Free Software Foundation, Inc.
EXTRA_LOCALE_CATEGORIES =
PACKAGE_GNU =
MSGID_BUGS_ADDRESS =
USE_MSGCTXT = no
MSGMERGE_OPTIONS =
MSGINIT_OPTIONS =
PO_DEPENDS_ON_POT = yes
DIST_DEPENDS_ON_UPDATE_PO = yes

.SUFFIXES:
.SUFFIXES: .po .gmo .mo .sed .sin .nop .po-create .po-update

.po.mo:
	@echo "$(MSGFMT) -c -o $@ $<"; \
	$(MSGFMT) -c -o t-$@ $< && mv t-$@ $@

.po.gmo:
	@lang=`echo $* | sed -e 's,.*/,,'`; \
	test "$(srcdir)" = . && cdcmd="" || cdcmd="cd $(srcdir) && "; \
	echo "$${cdcmd}rm -f $${lang}.gmo && $(GMSGFMT) -c --statistics --verbose -o $${lang}.gmo $${lang}.po"; \
	cd $(srcdir) && rm -f $${lang}.gmo && $(GMSGFMT) -c --statistics --verbose -o t-$${lang}.gmo $${lang}.po && mv t-$${lang}.gmo $${lang}.gmo

.sin.sed:
	sed -e '/^#/d' $< > t-$@
	mv t-$@ $@


all: all-no

all-yes: stamp-po
all-no:

# Ensure that the gettext macros and this Makefile.in.in are in sync.
CHECK_MACRO_VERSION = \
	test "$(GETTEXT_MACRO_VERSION)" = "0.19" \
	  || { echo "*** error: gettext infrastructure mismatch: using a Makefile.in.in from gettext version $(GETTEXT_MACRO_VERSION) but the autoconf macros are from gettext version 0.19" 1>&2; \
	       exit 1; \
	     }

# $(srcdir)/$(DOMAIN).pot is only created when needed. When xgettext finds no
# internationalized messages, no $(srcdir)/$(DOMAIN).pot is created (because
# we don't want to bother translators with empty POT files). We assume that
# LINGUAS is empty in this case, i.e. $(POFILES) and $(GMOFILES) are empty.
# In this case, stamp-po is a nop (i.e. a phony target).

# stamp-po is a timestamp denoting the last time at which the CATALOGS have
# been loosely updated. Its purpose is that when a developer or translator
# checks out the package via CVS, and the $(DOMAIN).pot file is not in CVS,
# "make" will update the $(DOMAIN).pot and the $(CATALOGS), but subsequent
# invocations of "make" will do nothing. This timestamp would not be necessary
# if updating the $(CATALOGS) would always touch them; however, the rule for
# $(POFILES) has been designed to not touch files that don't need to be
# changed.
stamp-po: $(srcdir)/$(DOMAIN).pot
	@$(CHECK_MACRO_VERSION)
	test ! -f $(srcdir)/$(DOMAIN).pot || \
	  test -z "$(GMOFILES)" || $(MAKE) $(GMOFILES)
	@test ! -f $(srcdir)/$(DOMAIN).pot || { \
	  echo "touch stamp-po" && \
	  echo timestamp > stamp-poT && \
	  mv stamp-poT stamp-po; \
	}

# Note: Target 'all' must not depend on target '$(DOMAIN).pot-update',
# otherwise packages like GCC can not be built if only parts of the source
# have been downloaded.

# This target rebuilds $(DOMAIN).pot; it is an expensive operation.
# Note that $(DOMAIN).pot is not touched if it doesn't need to be changed.
# The determination of whether the package xyz is a GNU one is based on the
# heuristic whether some file in the top level directory mentions "GNU xyz".
# If GNU 'find' is available, we avoid grepping through monster files.
$(DOMAIN).pot-update: $(POTFILES) $(srcdir)/POTFILES.in remove-potcdate.sed
	package_gnu="$(PACKAGE_GNU)"; \
	test -n "$$package_gnu" || { \
	  if { if (LC_ALL=C find --version) 2>/dev/null | grep GNU >/dev/null; then \
		 LC_ALL=C find -L $(top_srcdir) -maxdepth 1 -type f \
			       -size -10000000c -exec grep 'GNU sharutils' \
			       /dev/null '{}' ';' 2>/dev/null; \
	       else \
		 LC_ALL=C grep 'GNU sharutils' $(top_srcdir)/* 2>/dev/null; \
	       fi; \
	     } | grep -v 'libtool:' >/dev/null; then \
	     package_gnu=yes; \
	   else \
	     package_gnu=no; \
	   fi; \
	}; \
	if test "$$package_gnu" = "yes"; then \
	  package_prefix='GNU '; \
	else \
	  package_prefix=''; \
	fi; \
	if test -n '$(MSGID_BUGS_ADDRESS)' || test '$(PACKAGE_BUGREPORT)' = '@'PACKAGE_BUGREPORT'@'; then \
	  msgid_bugs_address='$(MSGID_BUGS_ADDRESS)'; \
	else \
	  msgid_bugs_address='$(PACKAGE_BUGREPORT)'; \
	fi; \
	case `$(XGETTEXT) --version | sed 1q | sed -e 's,^[^0-9]*,,'` in \
	  '' | 0.[0-9] | 0.[0-9].* | 0.1[0-5] | 0.1[0-5].* | 0.16 | 0.16.[0-1]*) \
	    $(XGETTEXT) --default-domain=$(DOMAIN) --directory=$(top_srcdir) \
	      --add-comments=TRANSLATORS: $(XGETTEXT_OPTIONS)  --flag=error:3:c-format --flag=error_at_line:5:c-format \
	      --files-from=$(srcdir)/POTFILES.in \
	      --copyright-holder='$(COPYRIGHT_HOLDER)' \
	      --msgid-bugs-address="$$msgid_bugs_address" \
	    ;; \
	  *) \
	    $(XGETTEXT) --default-domain=$(DOMAIN) --directory=$(top_srcdir) \
	      --add-comments=TRANSLATORS: $(XGETTEXT_OPTIONS)  --flag=error:3:c-format --flag=error_at_line:5:c-format \
	      --files-from=$(srcdir)/POTFILES.in \
	      --copyright-holder='$(COPYRIGHT_HOLDER)' \
	      --package-name="$${package_prefix}sharutils" \
	      --package-version='4.15' \
	      --msgid-bugs-address="$$msgid_bugs_address" \
	    ;; \
	esac
	test ! -f $(DOMAIN).po || { \
	  if test -f $(srcdir)/$(DOMAIN).pot; then \
	    sed -f remove-potcdate.sed < $(srcdir)/$(DOMAIN).pot > $(DOMAIN).1po && \
	    sed -f remove-potcdate.sed < $(DOMAIN).po > $(DOMAIN).2po && \
	    if cmp $(DOMAIN).1po $(DOMAIN).2po >/dev/null 2>&1; then \
	      rm -f $(DOMAIN).1po $(DOMAIN).2po $(DOMAIN).po; \
	    else \
	      rm -f $(DOMAIN).1po $(DOMAIN).2po $(srcdir)/$(DOMAIN).pot && \
	      mv $(DOMAIN).po $(srcdir)/$(DOMAIN).pot; \
	    fi; \
	  else \
	    mv $(DOMAIN).po $(srcdir)/$(DOMAIN).pot; \
	  fi; \
	}

# This rule has no dependencies: we don't need to update $(DOMAIN).pot at
# every "make" invocation, only create it when it is missing.
# Only "make $(DOMAIN).pot-update" or "make dist" will force an update.
$(srcdir)/$(DOMAIN).pot:
	$(MAKE) $(DOMAIN).pot-update

# This target rebuilds a PO file if $(DOMAIN).pot has changed.
# Note that a PO file is not touched if it doesn't need to be changed.
$(POFILES): $(POFILESDEPS)
	@lang=`echo $@ | sed -e 's,.*/,,' -e 's/\.po$$//'`; \
	if test -f "$(srcdir)/$${lang}.po"; then \
	  test -f $(srcdir)/$(DOMAIN).pot || $(MAKE) $(srcdir)/$(DOMAIN).pot; \
	  test "$(srcdir)" = . && cdcmd="" || cdcmd="cd $(srcdir) && "; \
	  echo "$${cdcmd}$(MSGMERGE_UPDATE) $(MSGMERGE_OPTIONS) --lang=$${lang} $${lang}.po $(DOMAIN).pot"; \
	  cd $(srcdir) \
	    && { case `$(MSGMERGE_UPDATE) --version | sed 1q | sed -e 's,^[^0-9]*,,'` in \
	           '' | 0.[0-9] | 0.[0-9].* | 0.1[0-7] | 0.1[0-7].*) \
	             $(MSGMERGE_UPDATE) $(MSGMERGE_OPTIONS) $${lang}.po $(DOMAIN).pot;; \
	           *) \
	             $(MSGMERGE_UPDATE) $(MSGMERGE_OPTIONS) --lang=$${lang} $${lang}.po $(DOMAIN).pot;; \
	         esac; \
	       }; \
	else \
	  $(MAKE) $${lang}.po-create; \
	fi


install: install-exec install-data
install-exec:
install-data: install-data-no
	if test "$(PACKAGE)" = "gettext-tools"; then \
	  $(mkdir_p) $(DESTDIR)$(gettextsrcdir); \
	  for file in $(DISTFILES.common) Makevars.template; do \
	    $(INSTALL_DATA) $(srcdir)/$$file \
			    $(DESTDIR)$(gettextsrcdir)/$$file; \
	  done; \
	  for file in Makevars; do \
	    rm -f $(DESTDIR)$(gettextsrcdir)/$$file; \
	  done; \
	else \
	  : ; \
	fi
install-data-no: all
install-data-yes: all
	@catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  lang=`echo $$cat | sed -e 's/\.gmo$$//'`; \
	  dir=$(localedir)/$$lang/LC_MESSAGES; \
	  $(mkdir_p) $(DESTDIR)$$dir; \
	  if test -r $$cat; then realcat=$$cat; else realcat=$(srcdir)/$$cat; fi; \
	  $(INSTALL_DATA) $$realcat $(DESTDIR)$$dir/$(DOMAIN).mo; \
	  echo "installing $$realcat as $(DESTDIR)$$dir/$(DOMAIN).mo"; \
	  for lc in '' $(EXTRA_LOCALE_CATEGORIES); do \
	    if test -n "$$lc"; then \
	      if (cd $(DESTDIR)$(localedir)/$$lang && LC_ALL=C ls -l -d $$lc 2>/dev/null) | grep ' -> ' >/dev/null; then \
	        link=`cd $(DESTDIR)$(localedir)/$$lang && LC_ALL=C ls -l -d $$lc | sed -e 's/^.* -> //'`; \
	        mv $(DESTDIR)$(localedir)/$$lang/$$lc $(DESTDIR)$(localedir)/$$lang/$$lc.old; \
	        mkdir $(DESTDIR)$(localedir)/$$lang/$$lc; \
	        (cd $(DESTDIR)$(localedir)/$$lang/$$lc.old && \
	         for file in *; do \
	           if test -f $$file; then \
	             ln -s ../$$link/$$file $(DESTDIR)$(localedir)/$$lang/$$lc/$$file; \
	           fi; \
	         done); \
	        rm -f $(DESTDIR)$(localedir)/$$lang/$$lc.old; \
	      else \
	        if test -d $(DESTDIR)$(localedir)/$$lang/$$lc; then \
	          :; \
	        else \
	          rm -f $(DESTDIR)$(localedir)/$$lang/$$lc; \
	          mkdir $(DESTDIR)$(localedir)/$$lang/$$lc; \
	        fi; \
	      fi; \
	      rm -f $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo; \
	      ln -s ../LC_MESSAGES/$(DOMAIN).mo $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo 2>/dev/null || \
	      ln $(DESTDIR)$(localedir)/$$lang/LC_MESSAGES/$(DOMAIN).mo $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo 2>/dev/null || \
	      cp -p $(DESTDIR)$(localedir)/$$lang/LC_MESSAGES/$(DOMAIN).mo $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo; \
	      echo "installing $$realcat link as $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo"; \
	    fi; \
	  done; \
	done

install-strip: install

installdirs: installdirs-exec installdirs-data
installdirs-exec:
installdirs-data: installdirs-data-no
	if test "$(PACKAGE)" = "gettext-tools"; then \
	  $(mkdir_p) $(DESTDIR)$(gettextsrcdir); \
	else \
	  : ; \
	fi
installdirs-data-no:
installdirs-data-yes:
	@catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  lang=`echo $$cat | sed -e 's/\.gmo$$//'`; \
	  dir=$(localedir)/$$lang/LC_MESSAGES; \
	  $(mkdir_p) $(DESTDIR)$$dir; \
	  for lc in '' $(EXTRA_LOCALE_CATEGORIES); do \
	    if test -n "$$lc"; then \
	      if (cd $(DESTDIR)$(localedir)/$$lang && LC_ALL=C ls -l -d $$lc 2>/dev/null) | grep ' -> ' >/dev/null; then \
	        link=`cd $(DESTDIR)$(localedir)/$$lang && LC_ALL=C ls -l -d $$lc | sed -e 's/^.* -> //'`; \
	        mv $(DESTDIR)$(localedir)/$$lang/$$lc $(DESTDIR)$(localedir)/$$lang/$$lc.old; \
	        mkdir $(DESTDIR)$(localedir)/$$lang/$$lc; \
	        (cd $(DESTDIR)$(localedir)/$$lang/$$lc.old && \
	         for file in *; do \
	           if test -f $$file; then \
	             ln -s ../$$link/$$file $(DESTDIR)$(localedir)/$$lang/$$lc/$$file; \
	           fi; \
	         done); \
	        rm -f $(DESTDIR)$(localedir)/$$lang/$$lc.old; \
	      else \
	        if test -d $(DESTDIR)$(localedir)/$$lang/$$lc; then \
	          :; \
	        else \
	          rm -f $(DESTDIR)$(localedir)/$$lang/$$lc; \
	          mkdir $(DESTDIR)$(localedir)/$$lang/$$lc; \
	        fi; \
	      fi; \
	    fi; \
	  done; \
	done

# Define this as empty until I found a useful application.
installcheck:

uninstall: uninstall-exec uninstall-data
uninstall-exec:
uninstall-data: uninstall-data-no
	if test "$(PACKAGE)" = "gettext-tools"; then \
	  for file in $(DISTFILES.common) Makevars.template; do \
	    rm -f $(DESTDIR)$(gettextsrcdir)/$$file; \
	  done; \
	else \
	  : ; \
	fi
uninstall-data-no:
uninstall-data-yes:
	catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  lang=`echo $$cat | sed -e 's/\.gmo$$//'`; \
	  for lc in LC_MESSAGES $(EXTRA_LOCALE_CATEGORIES); do \
	    rm -f $(DESTDIR)$(localedir)/$$lang/$$lc/$(DOMAIN).mo; \
	  done; \
	done

check: all

info dvi ps pdf html tags TAGS ctags CTAGS ID:

mostlyclean:
	rm -f remove-potcdate.sed
	rm -f stamp-poT
	rm -f core core.* $(DOMAIN).po $(DOMAIN).1po $(DOMAIN).2po *.new.po
	rm -fr *.o

clean: mostlyclean

distclean: clean
	rm -f Makefile Makefile.in POTFILES *.mo

maintainer-clean: distclean
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."
	rm -f stamp-po $(GMOFILES)

distdir = $(top_builddir)/$(PACKAGE)-$(VERSION)/$(subdir)
dist distdir:
	test -z "$(DISTFILESDEPS)" || $(MAKE) $(DISTFILESDEPS)
	@$(MAKE) dist2
# This is a separate target because 'update-po' must be executed before.
dist2: stamp-po $(DISTFILES)
	dists="$(DISTFILES)"; \
	if test "$(PACKAGE)" = "gettext-tools"; then \
	  dists="$$dists Makevars.template"; \
	fi; \
	if test -f $(srcdir)/$(DOMAIN).pot; then \
	  dists="$$dists $(DOMAIN).pot stamp-po"; \
	fi; \
	if test -f $(srcdir)/ChangeLog; then \
	  dists="$$dists ChangeLog"; \
	fi; \
	for i in 0 1 2 3 4 5 6 7 8 9; do \
	  if test -f $(srcdir)/ChangeLog.$$i; then \
	    dists="$$dists ChangeLog.$$i"; \
	  fi; \
	done; \
	if test -f $(srcdir)/LINGUAS; then dists="$$dists LINGUAS"; fi; \
	for file in $$dists; do \
	  if test -f $$file; then \
	    cp -p $$file $(distdir) || exit 1; \
	  else \
	    cp -p $(srcdir)/$$file $(distdir) || exit 1; \
	  fi; \
	done

update-po: Makefile
	$(MAKE) $(DOMAIN).pot-update
	test -z "$(UPDATEPOFILES)" || $(MAKE) $(UPDATEPOFILES)
	$(MAKE) update-gmo

# General rule for creating PO files.

.nop.po-create:
	@lang=`echo $@ | sed -e 's/\.po-create$$//'`; \
	echo "File $$lang.po does not exist. If you are a translator, you can create it through 'msginit'." 1>&2; \
	exit 1

# General rule for updating PO files.

.nop.po-update:
	@lang=`echo $@ | sed -e 's/\.po-update$$//'`; \
	if test "$(PACKAGE)" = "gettext-tools"; then PATH=`pwd`/../src:$$PATH; fi; \
	tmpdir=`pwd`; \
	echo "$$lang:"; \
	test "$(srcdir)" = . && cdcmd="" || cdcmd="cd $(srcdir) && "; \
	echo "$${cdcmd}$(MSGMERGE) $(MSGMERGE_OPTIONS) --lang=$$lang $$lang.po $(DOMAIN).pot -o $$lang.new.po"; \
	cd $(srcdir); \
	if { case `$(MSGMERGE) --version | sed 1q | sed -e 's,^[^0-9]*,,'` in \
	       '' | 0.[0-9] | 0.[0-9].* | 0.1[0-7] | 0.1[0-7].*) \
	         $(MSGMERGE) $(MSGMERGE_OPTIONS) -o $$tmpdir/$$lang.new.po $$lang.po $(DOMAIN).pot;; \
	       *) \
	         $(MSGMERGE) $(MSGMERGE_OPTIONS) --lang=$$lang -o $$tmpdir/$$lang.new.po $$lang.po $(DOMAIN).pot;; \
	     esac; \
	   }; then \
	  if cmp $$lang.po $$tmpdir/$$lang.new.po >/dev/null 2>&1; then \
	    rm -f $$tmpdir/$$lang.new.po; \
	  else \
	    if mv -f $$tmpdir/$$lang.new.po $$lang.po; then \
	      :; \
	    else \
	      echo "msgmerge for $$lang.po failed: cannot move $$tmpdir/$$lang.new.po to $$lang.po" 1>&2; \
	      exit 1; \
	    fi; \
	  fi; \
	else \
	  echo "msgmerge for $$lang.po failed!" 1>&2; \
	  rm -f $$tmpdir/$$lang.new.po; \
	fi

$(DUMMYPOFILES):

update-gmo: Makefile $(GMOFILES)
	@:

# Recreate Makefile by invoking config.status. Explicitly invoke the shell,
# because execution permission bits may not work on the current file system.
# Use /bin/bash, which is the shell determined by autoconf for the use by its
# scripts, not $(SHELL) which is hardwired to /bin/sh and may be deficient.
Makefile: Makefile.in.in Makevars $(top_builddir)/config.status POTFILES.in LINGUAS
	cd $(top_builddir) \
	  && /bin/bash ./config.status $(subdir)/$@.in po-directories

force:

# Tell versions [3.59,3.63) of GNU make not to export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
# This file, Rules-quot, can be copied and used freely without restrictions.
# Special Makefile rules for English message catalogs with quotation marks.

DISTFILES.common.extra1 = quot.sed boldquot.sed en@quot.header en@boldquot.header insert-header.sin Rules-quot

.SUFFIXES: .insert-header .po-update-en

en@quot.po-create:
	$(MAKE) en@quot.po-update
en@boldquot.po-create:
	$(MAKE) en@boldquot.po-update

en@quot.po-update: en@quot.po-update-en
en@boldquot.po-update: en@boldquot.po-update-en

.insert-header.po-update-en:
	@lang=`echo $@ | sed -e 's/\.po-update-en$$//'`; \
	if test "$(PACKAGE)" = "gettext-tools"; then PATH=`pwd`/../src:$$PATH; GETTEXTLIBDIR=`cd $(top_srcdir)/src && pwd`; export GETTEXTLIBDIR; fi; \
	tmpdir=`pwd`; \
	echo "$$lang:"; \
	ll=`echo $$lang | sed -e 's/@.*//'`; \
	LC_ALL=C; export LC_ALL; \
	cd $(srcdir); \
	if $(MSGINIT) $(MSGINIT_OPTIONS) -i $(DOMAIN).pot --no-translator -l $$lang -o - 2>/dev/null \
	   | $(SED) -f $$tmpdir/$$lang.insert-header | $(MSGCONV) -t UTF-8 | \
	   { case `$(MSGFILTER) --version | sed 1q | sed -e 's,^[^0-9]*,,'` in \
	     '' | 0.[0-9] | 0.[0-9].* | 0.1[0-8] | 0.1[0-8].*) \
	       $(MSGFILTER) $(SED) -f `echo $$lang | sed -e 's/.*@//'`.sed \
	       ;; \
	     *) \
	       $(MSGFILTER) `echo $$lang | sed -e 's/.*@//'` \
	       ;; \
	     esac } 2>/dev/null > $$tmpdir/$$lang.new.po \
	     ; then \
	  if cmp $$lang.po $$tmpdir/$$lang.new.po >/dev/null 2>&1; then \
	    rm -f $$tmpdir/$$lang.new.po; \
	  else \
	    if mv -f $$tmpdir/$$lang.new.po $$lang.po; then \
	      :; \
	    else \
	      echo "creation of $$lang.po failed: cannot move $$tmpdir/$$lang.new.po to $$lang.po" 1>&2; \
	      exit 1; \
	    fi; \
	  fi; \
	else \
	  echo "creation of $$lang.po failed!" 1>&2; \
	  rm -f $$tmpdir/$$lang.new.po; \
	fi

en@quot.insert-header: insert-header.sin
	sed -e '/^#/d' -e 's/HEADER/en@quot.header/g' $(srcdir)/insert-header.sin > en@quot.insert-header

en@boldquot.insert-header: insert-header.sin
	sed -e '/^#/d' -e 's/HEADER/en@boldquot.header/g' $(srcdir)/insert-header.sin > en@boldquot.insert-header

mostlyclean: mostlyclean-quot
mostlyclean-quot:
	rm -f *.insert-header

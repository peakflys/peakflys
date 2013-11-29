SUBDIRS = public server

.PHONY : all debug ctags
all:debug

debug:
	@for DIR in $(SUBDIRS); \
	do \
		$(MAKE) -C $$DIR || exit 1; \
	done
ctags:
	ctags -R -h ".c.cpp.h" -o tags

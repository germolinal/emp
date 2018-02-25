# GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  Lua_config = debug
  emp_core_config = debug
  emp_config = debug
  rtrad_config = debug
endif
ifeq ($(config),release)
  Lua_config = release
  emp_core_config = release
  emp_config = release
  rtrad_config = release
endif

PROJECTS := Lua emp_core emp rtrad

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

Lua:
ifneq (,$(Lua_config))
	@echo "==== Building Lua ($(Lua_config)) ===="
	@${MAKE} --no-print-directory -C premakescripts -f Lua.make config=$(Lua_config)
endif

emp_core: rtrad
ifneq (,$(emp_core_config))
	@echo "==== Building emp_core ($(emp_core_config)) ===="
	@${MAKE} --no-print-directory -C premakescripts -f emp_core.make config=$(emp_core_config)
endif

emp: Lua emp_core
ifneq (,$(emp_config))
	@echo "==== Building emp ($(emp_config)) ===="
	@${MAKE} --no-print-directory -C premakescripts -f emp.make config=$(emp_config)
endif

rtrad:
ifneq (,$(rtrad_config))
	@echo "==== Building rtrad ($(rtrad_config)) ===="
	@${MAKE} --no-print-directory -C premakescripts -f rtrad.make config=$(rtrad_config)
endif

clean:
	@${MAKE} --no-print-directory -C premakescripts -f Lua.make clean
	@${MAKE} --no-print-directory -C premakescripts -f emp_core.make clean
	@${MAKE} --no-print-directory -C premakescripts -f emp.make clean
	@${MAKE} --no-print-directory -C premakescripts -f rtrad.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   Lua"
	@echo "   emp_core"
	@echo "   emp"
	@echo "   rtrad"
	@echo ""
	@echo "For more information, see http://industriousone.com/premake/quick-start"
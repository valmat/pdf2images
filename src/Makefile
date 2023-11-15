
# CPP   = g++
# LD    = g++
CPP   = clang++
LD    = clang++

CPP_STD  = c++17


#compiler flags
# -Weffc++ -- не реально собрать с этой опцией с кучей стороннего кода
OPT_FLAG   = -pedantic -Wall -Wextra -Wsequence-point -Wno-unused-parameter

# INCL_LIBS =                                  \
# 	$(shell pkg-config --cflags poppler-cpp) \
# 	$(shell pkg-config --cflags Magick++)    \
# 	$(shell pkg-config --cflags dbus-cpp)    \
# 	$(shell pkg-config --cflags tesseract)


INCL_LIBS = $(shell pkg-config --cflags poppler-cpp)


INCLUDES   = -I. -I"./cpp" -I"../deps/cpputils" -I"../deps/IniConfigs/include/" -I"../deps/derot/include/" -I"../deps/httplib" -I"./cppdeps" ${INCL_LIBS}


CPP_FLAGS  = -std=${CPP_STD} ${OPT_FLAG} ${INCLUDES} -pthread -DCPPHTTPLIB_OPENSSL_SUPPORT
LD_FLAGS   = -std=${CPP_STD} ${OPT_FLAG}
# LD_LIBS    = -pthread -lpthread -lssl -lcrypto     \
# 	-Wl,-Bstatic -lz -ldl -lzbar -Wl,-Bdynamic     \
# 	-lv8                                           \
# 	$(shell pkg-config --libs   poppler-cpp)       \
# 	$(shell pkg-config --libs   Magick++)          \
# 	$(shell pkg-config --libs   dbus-cpp)          \
# 	$(shell pkg-config --libs   lept)              \
# 	$(shell pkg-config --libs   tesseract)

LD_LIBS    = -pthread -lpthread      \
	-Wl,-Bstatic -lz -ldl -lzbar -Wl,-Bdynamic     \
	-lv8                                           \
	$(shell pkg-config --libs   poppler-cpp)


STRIPBIN = true
version_color= \033[1;33m


SOURCES_deps = $(shell find -L cppdeps/ -type f -name '*.cpp')
SOURCES_subm = $(shell find -L cpp/     -type f -name '*.cpp')
EXECS_SRC    = $(shell find -L . -maxdepth 1 -type f -name '*.cpp')


ifeq ($(BUILD),release)   
	# "Release" build - optimization, and no debug symbols
	# opt `-s` : Remove all symbol table and relocation information from the executable.
	# https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html#index-s
	OPT_FLAG += -O3 -DNDEBUG
	CPP   = g++
	LD    = g++
	LD_FLAGS = -std=${CPP_STD} ${OPT_FLAG} -s -flto
	CPP_FLAGS += -flto

	STRIPBIN = strip --strip-all
	version_color = \033[1;32m

else
	# "Debug" build - no optimization, and debugging symbols
	OPT_FLAG += -O0 -g -DDEBUG_BUILD
endif

ifeq ($(CHECKER),pv)   
	PV_CFG := ../pv.cfg
	PVCHECK := pvs-studio
	CPP   := g++
	LD    := g++
	PREPROCESSOR := g++
else
	PV_CFG  := 
	PREPROCESSOR := true
	PVCHECK := true
endif

############################################################
CPUS=$(shell nproc)
MAKEFLAGS += --jobs=${CPUS}

.PHONY: clean release pv cppcheck all

EXECS_OBJ := $(patsubst ./%.cpp,o/%.o,$(EXECS_SRC))
EXECS_BIN := $(patsubst o/%.o,bin/%.bin,$(EXECS_OBJ))

SOURCES   := $(SOURCES_subm) $(SOURCES_deps)
OBJECTS   := $(patsubst %.cpp,o/%.o,$(SOURCES))

version=$(shell git -C "." describe --tags --candidates=1  2> /dev/null || echo "v0.0.0-nogit")

ADD_FLAGS :=-DVER="\"${version}\""


all: $(EXECS_BIN)
	@echo
	@echo "\033[1;36mBuild ${version_color}${version}\033[1;36m complite \033[0m"

# make release version
release:
	@$(eval MAKEFLAGS = "")
	@make "BUILD=release" -j`nproc`


pv:
	@make "CHECKER=pv" -j`nproc`


$(EXECS_OBJ) : o/%.o : ./%.cpp
	${CPP} ${CPP_FLAGS} ${ADD_FLAGS} -c $< -o $@

$(OBJECTS) : o/%.o : %.cpp
	@mkdir -p $(dir $(@))
	${CPP} ${CPP_FLAGS} ${ADD_FLAGS} -c $< -o $@
	@$(PREPROCESSOR) -E $< -o $<.i ${CPP_FLAGS} ${ADD_FLAGS}
	@$(PVCHECK) --cfg $(PV_CFG) --source-file  $< --i-file $<.i --cl-params ${CPP_FLAGS} ${ADD_FLAGS}


$(EXECS_BIN) : bin/%.bin : o/%.o $(OBJECTS)
	${LD} ${LD_FLAGS} -o $@ $< $(OBJECTS) ${LD_LIBS}
	@$(STRIPBIN) $@
	@echo ""

clean:
	@find o/   -type f -name '*.o'   -delete
	@find o/   -mindepth 1 -type d   -delete
	@find bin/ -type f -name '*.bin' -delete
	@find cpp/ -type f -name '*.i' -delete
	@find cppdeps/ -type f -name '*.i' -delete
	@echo "\033[1;32mClean complite\033[0m"

cppcheck:
	cppcheck --force -I. -I"./cpp" -I"../deps/cpputils" -I"../deps/IniConfigs/include/" -I /usr/include/v8 -I/usr/include/poppler/cpp -I/usr/include/poppler .


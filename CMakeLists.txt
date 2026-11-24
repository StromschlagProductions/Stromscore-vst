cmake_minimum_required(VERSION 3.22)
# Versionsnummer steht in der Datei VERSION (wird bei jeder Aenderung hochgezaehlt)
file(STRINGS VERSION STROMSCORE_VERSION LIMIT_COUNT 1)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS VERSION)
project(Stromscore VERSION ${STROMSCORE_VERSION})

# Private development artifacts may label the GUI; numeric plugin/release versions stay unchanged.
set(STROMSCORE_DEVELOPMENT_LABEL "" CACHE STRING "Optional development build label")
set(STROMSCORE_DISPLAY_VERSION "${STROMSCORE_VERSION}")
if(STROMSCORE_DEVELOPMENT_LABEL)
    string(APPEND STROMSCORE_DISPLAY_VERSION " ${STROMSCORE_DEVELOPMENT_LABEL}")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Laufzeitbibliothek fest einbinden: das Plugin braucht dann kein VC++-Redistributable
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

option(ENGINE_ONLY "Nur die Tests des Notengenerators bauen (ohne JUCE)" OFF)
include(CTest)
if(BUILD_TESTING)
    add_executable(BassPhraseTests Tests/BassPhraseTests.cpp)
    target_include_directories(BassPhraseTests PRIVATE Source)
    add_test(NAME BassPhrases COMMAND BassPhraseTests)
    if(MSVC)
        target_compile_options(BassPhraseTests PRIVATE /utf-8)
    endif()
    add_executable(BassPhraseProbe tools/bass_phrase_probe.cpp)
    target_include_directories(BassPhraseProbe PRIVATE Source)
    target_compile_definitions(BassPhraseProbe PRIVATE BASS_DIAGNOSTICS=1)
    if(MSVC)
        target_compile_options(BassPhraseProbe PRIVATE /utf-8)
    endif()
    add_executable(ModalTests Tests/ModalTests.cpp)
    target_include_directories(ModalTests PRIVATE Source)
    add_test(NAME ModalPassing COMMAND ModalTests)
    add_executable(ModalProbe tools/hook_development_probe.cpp)
    target_include_directories(ModalProbe PRIVATE Source)
    target_compile_definitions(ModalProbe PRIVATE BASS_REGRESSION_CONTROL=1)
    target_compile_definitions(ModalProbe PRIVATE HOOK_DIAGNOSTICS=1 MODAL_DIAGNOSTICS=1)
    if(MSVC)
        target_compile_options(ModalTests PRIVATE /utf-8)
        target_compile_options(ModalProbe PRIVATE /utf-8)
    endif()
    add_executable(HookDevelopmentTests Tests/HookDevelopmentTests.cpp)
    target_include_directories(HookDevelopmentTests PRIVATE Source)
    add_test(NAME HookDevelopment COMMAND HookDevelopmentTests)
    add_executable(HookDevelopmentProbe tools/hook_development_probe.cpp)
    target_include_directories(HookDevelopmentProbe PRIVATE Source)
    target_compile_definitions(HookDevelopmentProbe PRIVATE BASS_REGRESSION_CONTROL=1)
    target_compile_definitions(HookDevelopmentProbe PRIVATE HOOK_DIAGNOSTICS=1 PASSING_CONTROL=1)
    if(MSVC)
        target_compile_options(HookDevelopmentTests PRIVATE /utf-8)
        target_compile_options(HookDevelopmentProbe PRIVATE /utf-8)
    endif()
    add_executable(PopMemoryTests Tests/PopMemoryTests.cpp)
    target_include_directories(PopMemoryTests PRIVATE Source)
    if(MSVC)
        target_compile_options(PopMemoryTests PRIVATE /utf-8)
    endif()
    add_test(NAME PopMemory COMMAND PopMemoryTests)
    add_executable(CompositionCoreTests Tests/CompositionCoreTests.cpp)
    target_include_directories(CompositionCoreTests PRIVATE Source)
    if(MSVC)
        target_compile_options(CompositionCoreTests PRIVATE /utf-8)
    endif()
    add_test(NAME CompositionCore COMMAND CompositionCoreTests)
    add_executable(HarmonicProfileTests Tests/HarmonicProfileTests.cpp)
    target_include_directories(HarmonicProfileTests PRIVATE Source)
    if(MSVC)
        target_compile_options(HarmonicProfileTests PRIVATE /utf-8)
    endif()
    add_test(NAME HarmonicProfiles COMMAND HarmonicProfileTests)
    add_executable(WendungTests Tests/WendungTests.cpp)
    target_include_directories(WendungTests PRIVATE Source)
    if(MSVC)
        target_compile_options(WendungTests PRIVATE /utf-8)
    endif()
    add_test(NAME WendungIds COMMAND WendungTests)
    add_executable(WendungInventory tools/wendung_inventory.cpp)
    target_include_directories(WendungInventory PRIVATE Source)
    if(MSVC)
        target_compile_options(WendungInventory PRIVATE /utf-8)
    endif()
    find_package(Python3 COMPONENTS Interpreter QUIET)
    if(Python3_Interpreter_FOUND)
        add_test(NAME WendungInventory COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_CURRENT_SOURCE_DIR}/scripts/build_wendung_inventory.py
            --exporter $<TARGET_FILE:WendungInventory> --check)
    endif()
    add_executable(PolicyTests Tests/PolicyTests.cpp)
    target_include_directories(PolicyTests PRIVATE Source)
    if(MSVC)
        target_compile_options(PolicyTests PRIVATE /utf-8)
    endif()
    add_test(NAME Policy COMMAND PolicyTests)
    add_executable(EngineTests Tests/EngineTests.cpp)
    target_include_directories(EngineTests PRIVATE Source)
    if(MSVC)
        target_compile_options(EngineTests PRIVATE /utf-8)
        # The growing single-function regression driver has many bounded EventList/Generator
        # fixtures. MSVC's 1 MiB default is smaller than Linux's 8 MiB test stack.
        # This affects only the test executable, never the plugin or its audio thread.
        target_link_options(EngineTests PRIVATE /STACK:8388608)
    endif()
    add_test(NAME Engine COMMAND EngineTests)
    add_executable(VoiceLeadingTests Tests/VoiceLeadingTests.cpp)
    target_include_directories(VoiceLeadingTests PRIVATE Source)
    if(MSVC)
        target_compile_options(VoiceLeadingTests PRIVATE /utf-8)
    endif()
    find_package(Git QUIET)
    if(GIT_FOUND)
        execute_process(COMMAND ${GIT_EXECUTABLE} show 22be37ee755391f3651d7f5718c2e3d302c722ea:Source/ScoreEngine.h
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} OUTPUT_VARIABLE STROMSCORE_REFERENCE
            RESULT_VARIABLE STROMSCORE_REFERENCE_STATUS ERROR_QUIET)
        if(STROMSCORE_REFERENCE_STATUS EQUAL 0)
            file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/ScoreEngine19.h" "${STROMSCORE_REFERENCE}")
            target_compile_definitions(VoiceLeadingTests PRIVATE REFERENCE_ENGINE_HEADER="${CMAKE_CURRENT_BINARY_DIR}/ScoreEngine19.h")
        else()
            message(STATUS "Released v1.9 reference unavailable: voice-leading invariants run without A/B comparison")
        endif()
    endif()
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/voice-leading-comparison")
    configure_file(docs/development/VOICE_LEADING.md "${CMAKE_CURRENT_BINARY_DIR}/voice-leading-comparison/README.md" COPYONLY)
    add_test(NAME VoiceLeading COMMAND VoiceLeadingTests "${CMAKE_CURRENT_BINARY_DIR}/voice-leading-comparison")
    add_executable(PopMemoryProbe tools/pop_memory_probe.cpp)
    target_include_directories(PopMemoryProbe PRIVATE Source)
    target_compile_definitions(PopMemoryProbe PRIVATE BASS_REGRESSION_CONTROL=1)
    target_compile_definitions(PopMemoryProbe PRIVATE POP_HOOK_REGRESSION=1)
    if(MSVC)
        target_compile_options(PopMemoryProbe PRIVATE /utf-8)
    endif()
    if(Python3_Interpreter_FOUND AND GIT_FOUND AND NOT MSVC)
        execute_process(COMMAND ${GIT_EXECUTABLE} cat-file -e 912d04c:Source/ScoreEngine.h
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE POP_REFERENCE_STATUS ERROR_QUIET)
        if(POP_REFERENCE_STATUS EQUAL 0)
            add_test(NAME PopMemoryRegression COMMAND ${Python3_EXECUTABLE}
                ${CMAKE_CURRENT_SOURCE_DIR}/scripts/compare_pop_memory.py --probe $<TARGET_FILE:PopMemoryProbe>
                --compiler ${CMAKE_CXX_COMPILER} --output ${CMAKE_CURRENT_BINARY_DIR}/pop-memory)
        endif()
    endif()
    if(Python3_Interpreter_FOUND AND GIT_FOUND AND NOT MSVC)
        add_test(NAME HookDevelopmentComparison COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_CURRENT_SOURCE_DIR}/scripts/compare_hook_development.py --probe $<TARGET_FILE:HookDevelopmentProbe>
            --compiler ${CMAKE_CXX_COMPILER} --output ${CMAKE_CURRENT_BINARY_DIR}/hook-development)
    endif()
    if(Python3_Interpreter_FOUND AND GIT_FOUND AND NOT MSVC)
        add_test(NAME ModalComparison COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_CURRENT_SOURCE_DIR}/scripts/compare_modal.py --probe $<TARGET_FILE:ModalProbe>
            --compiler ${CMAKE_CXX_COMPILER} --output ${CMAKE_CURRENT_BINARY_DIR}/modal-passing)
    endif()
    if(Python3_Interpreter_FOUND AND GIT_FOUND AND NOT MSVC)
        add_test(NAME BassPhraseComparison COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_CURRENT_SOURCE_DIR}/scripts/compare_bass_phrases.py --probe $<TARGET_FILE:BassPhraseProbe>
            --compiler ${CMAKE_CXX_COMPILER} --output ${CMAKE_CURRENT_BINARY_DIR}/bass-phrases)
    endif()
    add_executable(TransitionTests Tests/TransitionTests.cpp)
    target_include_directories(TransitionTests PRIVATE Source)
    add_test(NAME WendungTransitions COMMAND TransitionTests)
    add_executable(TransitionProbe tools/transition_probe.cpp)
    target_include_directories(TransitionProbe PRIVATE Source)
    target_compile_definitions(TransitionProbe PRIVATE BASS_REGRESSION_CONTROL=1)
    target_compile_definitions(TransitionProbe PRIVATE POP_HOOK_REGRESSION=1)
    target_compile_definitions(TransitionProbe PRIVATE ENTRY_DIAGNOSTICS=1)
    if(MSVC)
        target_compile_options(TransitionTests PRIVATE /utf-8)
        target_compile_options(TransitionProbe PRIVATE /utf-8)
    endif()
    if(Python3_Interpreter_FOUND AND GIT_FOUND AND NOT MSVC)
        execute_process(COMMAND ${GIT_EXECUTABLE} cat-file -e be09fea:Source/ScoreEngine.h
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE ENTRY_REFERENCE_STATUS ERROR_QUIET)
        if(ENTRY_REFERENCE_STATUS EQUAL 0)
            add_test(NAME TransitionComparison COMMAND ${Python3_EXECUTABLE}
                ${CMAKE_CURRENT_SOURCE_DIR}/scripts/compare_transitions.py
                --probe $<TARGET_FILE:TransitionProbe> --compiler ${CMAKE_CXX_COMPILER}
                --output ${CMAKE_CURRENT_BINARY_DIR}/transition-comparison)
        endif()
    endif()
    add_executable(MotifDevelopmentTests Tests/MotifDevelopmentTests.cpp)
    target_include_directories(MotifDevelopmentTests PRIVATE Source)
    add_test(NAME MotifDevelopment COMMAND MotifDevelopmentTests)
    add_executable(VariationProbe tools/recurrence_probe.cpp)
    target_include_directories(VariationProbe PRIVATE Source)
    target_compile_definitions(VariationProbe PRIVATE BASS_REGRESSION_CONTROL=1)
    target_compile_definitions(VariationProbe PRIVATE POP_HOOK_REGRESSION=1)
    target_compile_definitions(VariationProbe PRIVATE RECURRENCE_DIAGNOSTICS=1 VARIATION_DIAGNOSTICS=1)
    if(MSVC)
        target_compile_options(MotifDevelopmentTests PRIVATE /utf-8)
        target_compile_options(VariationProbe PRIVATE /utf-8)
    endif()
    if(Python3_Interpreter_FOUND)
        add_test(NAME MotifDevelopmentComparison COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_CURRENT_SOURCE_DIR}/scripts/compare_motif_development.py
            --probe $<TARGET_FILE:VariationProbe> --output ${CMAKE_CURRENT_BINARY_DIR}/motif-development)
    endif()
    add_executable(RecurrenceProbe tools/recurrence_probe.cpp)
    target_include_directories(RecurrenceProbe PRIVATE Source)
    target_compile_definitions(RecurrenceProbe PRIVATE BASS_REGRESSION_CONTROL=1)
    target_compile_definitions(RecurrenceProbe PRIVATE POP_HOOK_REGRESSION=1)
    target_compile_definitions(RecurrenceProbe PRIVATE RECURRENCE_DIAGNOSTICS=1)
    if(MSVC)
        target_compile_options(RecurrenceProbe PRIVATE /utf-8)
    endif()
    if(Python3_Interpreter_FOUND AND GIT_FOUND AND NOT MSVC)
        execute_process(COMMAND ${GIT_EXECUTABLE} cat-file -e 920d388:Source/ScoreEngine.h
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE RECURRENCE_REFERENCE_STATUS ERROR_QUIET)
        if(RECURRENCE_REFERENCE_STATUS EQUAL 0)
            add_test(NAME RecurrenceComparison COMMAND ${Python3_EXECUTABLE}
                ${CMAKE_CURRENT_SOURCE_DIR}/scripts/compare_recurrence.py
                --probe $<TARGET_FILE:RecurrenceProbe> --compiler ${CMAKE_CXX_COMPILER}
                --output ${CMAKE_CURRENT_BINARY_DIR}/recurrence-comparison)
        endif()
    endif()
    add_executable(PhraseProbe tools/phrase_probe.cpp)
    target_include_directories(PhraseProbe PRIVATE Source)
    target_compile_definitions(PhraseProbe PRIVATE BASS_REGRESSION_CONTROL=1)
    target_compile_definitions(PhraseProbe PRIVATE POP_HOOK_REGRESSION=1)
    target_compile_definitions(PhraseProbe PRIVATE PHRASE_DIAGNOSTICS=1)
    if(MSVC)
        target_compile_options(PhraseProbe PRIVATE /utf-8)
    endif()
    if(Python3_Interpreter_FOUND AND GIT_FOUND AND NOT MSVC)
        execute_process(COMMAND ${GIT_EXECUTABLE} cat-file -e 0cc30c2:Source/ScoreEngine.h
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE PHRASE_REFERENCE_STATUS ERROR_QUIET)
        if(PHRASE_REFERENCE_STATUS EQUAL 0)
            add_test(NAME PhraseComparison COMMAND ${Python3_EXECUTABLE}
                ${CMAKE_CURRENT_SOURCE_DIR}/scripts/compare_phrases.py
                --probe $<TARGET_FILE:PhraseProbe> --compiler ${CMAKE_CXX_COMPILER}
                --output ${CMAKE_CURRENT_BINARY_DIR}/phrase-comparison)
        endif()
    endif()
    add_executable(DensityProbe tools/density_probe.cpp)
    target_include_directories(DensityProbe PRIVATE Source)
    target_compile_definitions(DensityProbe PRIVATE BASS_REGRESSION_CONTROL=1)
    target_compile_definitions(DensityProbe PRIVATE POP_HOOK_REGRESSION=1)
    if(MSVC)
        target_compile_options(DensityProbe PRIVATE /utf-8)
    endif()
    if(Python3_Interpreter_FOUND AND GIT_FOUND AND NOT MSVC)
        execute_process(COMMAND ${GIT_EXECUTABLE} cat-file -e 2f4dd47:Source/ScoreEngine.h
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE DENSITY_REFERENCE_STATUS ERROR_QUIET)
        if(DENSITY_REFERENCE_STATUS EQUAL 0)
            add_test(NAME DensityComparison COMMAND ${Python3_EXECUTABLE}
                ${CMAKE_CURRENT_SOURCE_DIR}/scripts/compare_density.py
                --probe $<TARGET_FILE:DensityProbe> --compiler ${CMAKE_CXX_COMPILER}
                --output ${CMAKE_CURRENT_BINARY_DIR}/density-comparison)
        endif()
    endif()
    add_executable(AccompanimentProbe tools/accompaniment_probe.cpp)
    target_include_directories(AccompanimentProbe PRIVATE Source)
    target_compile_definitions(AccompanimentProbe PRIVATE BASS_REGRESSION_CONTROL=1)
    target_compile_definitions(AccompanimentProbe PRIVATE POP_HOOK_REGRESSION=1)
    if(MSVC)
        target_compile_options(AccompanimentProbe PRIVATE /utf-8)
    endif()
    if(Python3_Interpreter_FOUND AND GIT_FOUND AND NOT MSVC)
        execute_process(COMMAND ${GIT_EXECUTABLE} cat-file -e 237b415:Source/ScoreEngine.h
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE COORDINATION_REFERENCE_STATUS ERROR_QUIET)
        if(COORDINATION_REFERENCE_STATUS EQUAL 0)
            add_test(NAME AccompanimentComparison COMMAND ${Python3_EXECUTABLE}
                ${CMAKE_CURRENT_SOURCE_DIR}/scripts/compare_accompaniment.py
                --probe $<TARGET_FILE:AccompanimentProbe> --compiler ${CMAKE_CXX_COMPILER}
                --output ${CMAKE_CURRENT_BINARY_DIR}/accompaniment-comparison)
        endif()
    endif()

endif()
if(ENGINE_ONLY)
    return()
endif()

set(STROMSCORE_JUCE_PATH "" CACHE PATH "Lokaler JUCE-Ordner (leer = automatisch laden)")
set(STROMSCORE_FORMATS "VST3" CACHE STRING "Plugin-Formate")

if(STROMSCORE_JUCE_PATH)
    add_subdirectory(${STROMSCORE_JUCE_PATH} JUCE)
else()
    include(FetchContent)
    FetchContent_Declare(JUCE
        GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
        GIT_TAG 8.0.9
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(JUCE)
endif()

juce_add_binary_data(StromscoreAssets SOURCES Assets/logo.png)

# Instrument ohne eigenen Klang (ausser Vorhoeren): erzeugt Noten und gibt sie als MIDI an andere Instrumentenspuren weiter
juce_add_plugin(Stromscore
    COMPANY_NAME "Stromschlag Audio"
    PLUGIN_MANUFACTURER_CODE Strm
    PLUGIN_CODE Stsc
    FORMATS ${STROMSCORE_FORMATS}
    PRODUCT_NAME "Stromscore"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT TRUE
    IS_MIDI_EFFECT FALSE
    VST3_CATEGORIES Instrument Generator
    COPY_PLUGIN_AFTER_BUILD FALSE)

target_sources(Stromscore PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp)

target_compile_definitions(Stromscore PUBLIC
    PLUGIN_VERSION_TEXT="${STROMSCORE_DISPLAY_VERSION}"
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_DISPLAY_SPLASH_SCREEN=0)

if(MSVC)
    target_compile_options(Stromscore PRIVATE /utf-8)
endif()

target_link_libraries(Stromscore
    PRIVATE
        StromscoreAssets
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

if(BUILD_TESTING)
    juce_add_console_app(ProcessorTests PRODUCT_NAME "Stromscore processor tests")
    target_sources(ProcessorTests PRIVATE Tests/ProcessorTests.cpp)
    target_include_directories(ProcessorTests PRIVATE Source $<TARGET_PROPERTY:Stromscore,INCLUDE_DIRECTORIES>)
    target_compile_definitions(ProcessorTests PRIVATE JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0)
    if(MSVC)
        target_compile_options(ProcessorTests PRIVATE /utf-8)
    endif()
    target_link_libraries(ProcessorTests PRIVATE Stromscore)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        target_compile_definitions(ProcessorTests PRIVATE STROMSCORE_TRACK_C_HEAP=1)
        target_link_options(ProcessorTests PRIVATE "-Wl,--wrap=malloc,--wrap=realloc,--wrap=calloc")
    endif()
    add_test(NAME Processor COMMAND ProcessorTests)
endif()

# Screenshot-Werkzeug fuer README und Homepage (nicht Teil des Standard-Builds): cmake --build build --target StromscoreScreenshot
juce_add_console_app(StromscoreScreenshot PRODUCT_NAME "Stromscore screenshot")
target_sources(StromscoreScreenshot PRIVATE tools/screenshot.cpp)
target_include_directories(StromscoreScreenshot PRIVATE Source $<TARGET_PROPERTY:Stromscore,INCLUDE_DIRECTORIES>)
target_compile_definitions(StromscoreScreenshot PRIVATE JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0 PLUGIN_VERSION_TEXT="${STROMSCORE_DISPLAY_VERSION}")
if(MSVC)
    target_compile_options(StromscoreScreenshot PRIVATE /utf-8)
endif()
target_link_libraries(StromscoreScreenshot PRIVATE Stromscore)
set_target_properties(StromscoreScreenshot PROPERTIES EXCLUDE_FROM_ALL TRUE)

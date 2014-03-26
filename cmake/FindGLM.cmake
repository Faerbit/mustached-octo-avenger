if(APPLE)
    set(HEADER_SEARCH_PATH
        /usr/local
        /opt/local
        /usr/local/include
        /opt/local/include
    )
endif()
find_path(GLM_INCLUDE_DIR glm/glm.hpp ${HEADER_SEARCH_PATH})

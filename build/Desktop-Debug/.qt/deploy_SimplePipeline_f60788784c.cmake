include("/home/marcel/Dev/SimplePipeline/build/Desktop-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/SimplePipeline-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE /home/marcel/Dev/SimplePipeline/build/Desktop-Debug/SimplePipeline
    GENERATE_QT_CONF
)

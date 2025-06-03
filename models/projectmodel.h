#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include <QString>

/**
 * @brief The ProjectModel class represents a project.
 */
class ProjectModel
{
public:
    ProjectModel()
        : m_id(0),
        m_name(""),
        m_path(""),
        m_description(""),
        m_status(true),
        m_framerate(0),
        m_resolutionW(0),
        m_resolutionH(0)
    {}

    ProjectModel(unsigned id, const QString &name, const QString &path,
                 const QString &description, bool status,
                 unsigned framerate, unsigned resolutionW,
                 unsigned resolutionH)
        : m_id(id),
        m_name(name),
        m_path(path),
        m_description(description),
        m_status(status),
        m_framerate(framerate),
        m_resolutionH(resolutionH),
        m_resolutionW(resolutionW)
    {}

    unsigned id() const {return m_id;}
    QString name() const {return m_name;}
    QString path() const {return m_path;}
    QString description() const {return m_description;}
    bool status() const {return m_status;}
    unsigned framerate() const {return m_framerate;}
    unsigned resolutionW() const {return m_resolutionW;}
    unsigned resolutionH() const {return m_resolutionH;}

private:
    unsigned m_id;
    QString m_name;
    QString m_path;
    QString m_description;
    bool m_status;
    unsigned m_framerate;
    unsigned m_resolutionW;
    unsigned m_resolutionH;
};

#endif // PROJECTMODEL_H

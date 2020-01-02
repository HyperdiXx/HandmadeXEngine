#pragma once

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <runtime/types.h>
#include <xenpch.h>

namespace XEngine
{
    namespace Rendering
    {
        enum class ElementType
        {
            None,
            Bool,
            Int,
            Int2,
            Int3,
            Int4,
            Float,
            Float2,
            Float3,
            Float4,
            Mat3x3,
            Mat4x4
        };


        class BufferElement
        {
        public:
            std::string m_name; // own string impl 
            ElementType m_type;
            uint32 m_size;
            uint32 m_offset;

            BufferElement() = default;

            BufferElement(const std::string& name, ElementType type)
            {
                m_name = name;
                m_type = type;
                m_size = type_sizeof(type);
                m_offset = 0;
            }

            uint32 type_sizeof(ElementType type)
            {
                switch (type)
                {
                case XEngine::Rendering::ElementType::None:
                    return 0;
                case XEngine::Rendering::ElementType::Bool:
                    return 1;
                case XEngine::Rendering::ElementType::Int:
                    return 4;
                case XEngine::Rendering::ElementType::Int2:
                    return 4 * 2;
                case XEngine::Rendering::ElementType::Int3:
                    return 4 * 3;
                case XEngine::Rendering::ElementType::Int4:
                    return 4 * 4;
                case XEngine::Rendering::ElementType::Float:
                    return 4;
                case XEngine::Rendering::ElementType::Float2:
                    return 4 * 2;
                case XEngine::Rendering::ElementType::Float3:
                    return 4 * 3;
                case XEngine::Rendering::ElementType::Float4:
                    return 4 * 4;
                case XEngine::Rendering::ElementType::Mat3x3:
                    return 4 * 9;
                case XEngine::Rendering::ElementType::Mat4x4:
                    return 4 * 16;
                }

                // Log function !!!

                return 0;
            }


            uint32 element_type_count()
            {
                switch (m_type)
                {
                case XEngine::Rendering::ElementType::None:
                    return 0;
                case XEngine::Rendering::ElementType::Bool:
                case XEngine::Rendering::ElementType::Int:
                case XEngine::Rendering::ElementType::Float:
                    return 1;
                case XEngine::Rendering::ElementType::Int2:
                case XEngine::Rendering::ElementType::Float2:
                    return 2;
                case XEngine::Rendering::ElementType::Int3:
                case XEngine::Rendering::ElementType::Float3:
                    return 3;
                case XEngine::Rendering::ElementType::Int4:
                case XEngine::Rendering::ElementType::Float4:
                    return 4;
                case XEngine::Rendering::ElementType::Mat3x3:
                    return 9;
                case XEngine::Rendering::ElementType::Mat4x4:
                    return 16;
                }

                // Log function !!!

                return 0;
            }

        };

        class BufferLayout
        {
        public:
            BufferLayout() {};

            BufferLayout(const std::initializer_list<BufferElement>& elements) :
                m_elements(elements)
            {
                for (int i = 0; i < m_elements.size(); i++)
                {
                    uint32 offset = 0;
                    auto cur_element = m_elements.at(i);
                    cur_element.m_offset = offset;
                    offset += cur_element.m_size;
                    m_stride += cur_element.m_size;
                }
            }

            inline uint32 get_stride() const { return m_stride; }

            inline const std::vector<BufferElement>& get_elements() const { return m_elements; }
        private:

            void offset_and_stride()
            {
                for (int i = 0; i < m_elements.size(); i++)
                {
                    uint32 offset = 0;
                    auto cur_element = m_elements.at(i);
                    cur_element.m_offset = offset;
                    offset += cur_element.m_size;
                    m_stride += cur_element.m_size;
                }
            }

        private:
            std::vector<BufferElement> m_elements;
            uint32 m_stride = 0;
        };

        class VertexBuffer
        {
        public:
            virtual ~VertexBuffer() = default;

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual const BufferLayout& get_layout() const = 0;
            virtual void set_layout(const BufferLayout& layout) = 0;

            static VertexBuffer *create(real32* vertices, uint32 size);
        };
    }
}

#endif // !VERTEXBUFFER_H

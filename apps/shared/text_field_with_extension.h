#ifndef SHARED_TEXT_FIELD_WITH_EXTENSION_H
#define SHARED_TEXT_FIELD_WITH_EXTENSION_H

#include <escher/text_field.h>

namespace Shared {

class TextFieldWithExtension : public TextField {
public:
  TextFieldWithExtension(size_t extensionLength,
      Responder * parentResponder,
      char * textBuffer,
      char * draftTextBuffer,
      size_t textBufferSize,
      ::TextFieldDelegate * delegate = nullptr,
      bool hasTwoBuffers = true,
      KDText::FontSize size = KDText::FontSize::Large,
      float horizontalAlignment = 0.0f,
      float verticalAlignment = 0.5f,
      KDColor textColor = KDColorBlack,
      KDColor backgroundColor = KDColorWhite) :
    TextField(parentResponder, textBuffer, draftTextBuffer, textBufferSize, delegate, hasTwoBuffers, size, horizontalAlignment, verticalAlignment, textColor, backgroundColor),
    m_extensionLength(extensionLength)
  {}
private:
  void willSetCursorLocation(int * location) override;
  size_t m_extensionLength;
};

}

#endif
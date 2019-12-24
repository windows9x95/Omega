#ifndef APPS_EXAM_POP_UP_CONTROLLER_H
#define APPS_EXAM_POP_UP_CONTROLLER_H

#include <escher.h>
#include "exam_pop_up_controller_delegate.h"
#include "global_preferences.h"

class HighContrastButton : public Button {
public:
  using Button::Button;
  virtual KDColor highlightedBackgroundColor() const override { return Palette::ButtonBackgroundSelectedHighContrast; }
};

class ExamPopUpController : public ViewController {
public:
  ExamPopUpController(ExamPopUpControllerDelegate * delegate);
  void setTargetExamMode(GlobalPreferences::ExamMode mode);
  GlobalPreferences::ExamMode targetExamMode() const { return m_targetExamMode; }
  // View Controller
  View * view() override;
  void viewDidDisappear() override;
  // Responder
  void didBecomeFirstResponder() override;
  bool handleEvent(Ion::Events::Event event) override;
private:
  class ContentView : public View {
  public:
    ContentView(Responder * parentResponder);
    void drawRect(KDContext * ctx, KDRect rect) const override;
    void setSelectedButton(int selectedButton);
    int selectedButton();
    void setMessagesForExamMode(GlobalPreferences::ExamMode mode);
  private:
    constexpr static KDCoordinate k_buttonMargin = 10;
    constexpr static KDCoordinate k_buttonHeight = 20;
    constexpr static KDCoordinate k_topMargin = 12;
    constexpr static KDCoordinate k_paragraphHeight = 20;
    int numberOfSubviews() const override;
    View * subviewAtIndex(int index) override;
    void layoutSubviews() override;
    HighContrastButton m_cancelButton;
    HighContrastButton m_okButton;
    MessageTextView m_warningTextView;
    MessageTextView m_messageTextView1;
    MessageTextView m_messageTextView2;
    MessageTextView m_messageTextView3;
  };
  ContentView m_contentView;
  GlobalPreferences::ExamMode m_targetExamMode;
  ExamPopUpControllerDelegate * m_delegate;
};

#endif


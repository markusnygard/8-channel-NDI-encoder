/* -LICENSE-START-
** Copyright (c) 2020 Blackmagic Design
**  
** Permission is hereby granted, free of charge, to any person or organization 
** obtaining a copy of the software and accompanying documentation (the 
** "Software") to use, reproduce, display, distribute, sub-license, execute, 
** and transmit the Software, and to prepare derivative works of the Software, 
** and to permit third-parties to whom the Software is furnished to do so, in 
** accordance with:
** 
** (1) if the Software is obtained from Blackmagic Design, the End User License 
** Agreement for the Software Development Kit (“EULA”) available at 
** https://www.blackmagicdesign.com/EULA/DeckLinkSDK; or
** 
** (2) if the Software is obtained from any third party, such licensing terms 
** as notified by that third party,
** 
** and all subject to the following:
** 
** (3) the copyright notices in the Software and this entire statement, 
** including the above license grant, this restriction and the following 
** disclaimer, must be included in all copies of the Software, in whole or in 
** part, and all derivative works of the Software, unless such copies or 
** derivative works are solely in the form of machine-executable object code 
** generated by a source language processor.
** 
** (4) THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
** FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT 
** SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE 
** FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE, 
** ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
** DEALINGS IN THE SOFTWARE.
** 
** A copy of the Software is available free of charge at 
** https://www.blackmagicdesign.com/desktopvideo_sdk under the EULA.
** 
** -LICENSE-END-
*/

#pragma once

#include <atomic>
#include <mutex>
#include <QOpenGLWidget>
#include "com_ptr.h"
#include "DeckLinkAPI.h"

class DeckLinkOpenGLDelegate : public QObject, public IDeckLinkScreenPreviewCallback
{
	Q_OBJECT

public:
	DeckLinkOpenGLDelegate();
	virtual ~DeckLinkOpenGLDelegate() = default;
	
	// IUnknown
	HRESULT		QueryInterface(REFIID iid, LPVOID *ppv) override;
	ULONG		AddRef() override;
	ULONG		Release() override;

	// IDeckLinkScreenPreviewCallback
	HRESULT		DrawFrame(IDeckLinkVideoFrame* theFrame) override;

signals:
	void		frameArrived(com_ptr<IDeckLinkVideoFrame> frame);

private:
	std::atomic<ULONG>		m_refCount;
};

class DeckLinkOpenGLWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	DeckLinkOpenGLWidget(QWidget* parent = nullptr);
	virtual ~DeckLinkOpenGLWidget() = default;

	IDeckLinkScreenPreviewCallback* delegate(void) const { return m_delegate.get(); }

	void clear();

protected:
	// QOpenGLWidget
	void	initializeGL() override;
	void	paintGL() override;
	void	resizeGL(int width, int height) override;

private slots:
	void	setFrame(com_ptr<IDeckLinkVideoFrame> frame);

private:
	com_ptr<DeckLinkOpenGLDelegate>			m_delegate;
	com_ptr<IDeckLinkGLScreenPreviewHelper>	m_deckLinkScreenPreviewHelper;
	std::mutex								m_mutex;
};

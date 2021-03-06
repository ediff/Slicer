/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Julien Finet, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

// QT includes
#include <QApplication>
#include <QTimer>

// qMRML includes
#include "qMRMLColorPickerWidget.h"

// MRML includes
#include <vtkMRMLColorTableNode.h>
#include <vtkMRMLFreeSurferProceduralColorNode.h>
#include <vtkMRMLPETProceduralColorNode.h>
#include <vtkMRMLScene.h>

// VTK includes
#include <vtkNew.h>

// STD includes

int qMRMLColorPickerWidgetTest3(int argc, char * argv [])
{
  QApplication app(argc, argv);

  qMRMLColorPickerWidget colorPickerWidget;

  vtkNew<vtkMRMLScene> scene;

  vtkNew<vtkMRMLColorTableNode> colorTableNode;
  colorTableNode->SetType(vtkMRMLColorTableNode::Labels);
  scene->AddNode(colorTableNode.GetPointer());
  
  colorPickerWidget.setMRMLScene(scene.GetPointer());

  vtkNew<vtkMRMLFreeSurferProceduralColorNode> colorFreeSurferNode;
  colorFreeSurferNode->SetTypeToRedBlue();
  scene->AddNode(colorFreeSurferNode.GetPointer());


  // for some reasons it generate a warning if the type is changed.
  colorTableNode->NamesInitialisedOff();
  colorTableNode->SetTypeToCool1();

  vtkNew<vtkMRMLPETProceduralColorNode> colorPETNode;
  colorPETNode->SetTypeToRainbow();
  scene->AddNode(colorPETNode.GetPointer());
  
  colorPickerWidget.show();

  if (argc < 2 || QString(argv[1]) != "-I" )
    {
    QTimer::singleShot(200, &app, SLOT(quit()));
    }

  return app.exec();
}


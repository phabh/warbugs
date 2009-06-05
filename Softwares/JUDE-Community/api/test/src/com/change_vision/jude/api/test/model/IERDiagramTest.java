package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IERDiagram;
import com.change_vision.jude.api.inf.model.IERModel;
import com.change_vision.jude.api.inf.model.IERSchema;

public class IERDiagramTest extends ITestCase {
    private IERSchema schema = null;

    public static Test suite() {
      return suite("testModel/judeAPITest/ERAPITest.jude", IERDiagramTest.class);
    }
    
    protected void setUp() {
        IERModel erModel = (IERModel)getElement(project.getOwnedElements(), "ER_Model");
        schema = erModel.getSchemata()[0];
    }
    
    public void testGetERDiagram() {
        IERDiagram dgm = (IERDiagram)getElement(schema.getDiagrams(), "ER_Diagram0");
        assertNotNull(dgm);
    }
}

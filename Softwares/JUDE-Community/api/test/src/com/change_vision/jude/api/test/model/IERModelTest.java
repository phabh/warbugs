package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IERModel;

public class IERModelTest extends ITestCase {
    private IERModel erModel = null;

    public static Test suite() {
        return suite("testModel/judeAPITest/ERAPITest.jude", IERModelTest.class);
    }
    
    protected void setUp() {
        erModel = (IERModel)getElement(project.getOwnedElements(), "ER_Model");
    }
    
    public void testGetERModel() {
        assertNotNull(erModel);
    }
}

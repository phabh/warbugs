package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IActivityDiagram;
import com.change_vision.jude.api.inf.model.IDiagram;

public class IActivityDiagramTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IActivityDiagramTest.jude", IActivityDiagramTest.class);
    }

    public void testGetActivity() {
        IActivityDiagram dgm = getDiagram();
        assertNotNull(dgm.getActivity().getName());
    }

    private IActivityDiagram getDiagram() {
        IDiagram[] dgms = project.getDiagrams();
        for (int i = 0; i < dgms.length; i++) {
            IDiagram diagram = dgms[i];
            if ("ActivityDiagram0".equals(diagram.getName())) {
                return (IActivityDiagram)diagram;
            }
        }
        fail("no diagram");
        return null;
    }
}

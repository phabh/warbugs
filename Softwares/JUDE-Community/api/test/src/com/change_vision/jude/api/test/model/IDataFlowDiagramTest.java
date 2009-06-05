package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IActivityDiagram;
import com.change_vision.jude.api.inf.model.IDataFlow;
import com.change_vision.jude.api.inf.model.IDataFlowDiagram;
import com.change_vision.jude.api.inf.model.IDataFlowNode;
import com.change_vision.jude.api.inf.model.IDiagram;

public class IDataFlowDiagramTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IDataFlowDiagramTest.jude", IDataFlowDiagramTest.class);
    }

    public void testGetDataFlowDiagram() {
    	IDataFlowDiagram dgm = getDiagram();
        assertNotNull(dgm.getName());
    }
    
    public void testDataFlows() {
    	IDataFlowDiagram dgm = getDiagram();
    	IDataFlow[] dfs = dgm.getDataFlows();
    	assertEquals(dfs.length, 6);
    }
    
    public void testDataFlowNodes() {
    	IDataFlowDiagram dgm = getDiagram();
    	IDataFlowNode[] dfns = dgm.getDataFlowNodes();
    	assertEquals(dfns.length, 7);
    }

    private IDataFlowDiagram getDiagram() {
        IDiagram[] dgms = project.getDiagrams();
        for (int i = 0; i < dgms.length; i++) {
            IDiagram diagram = dgms[i];
            if ("Data Flow Diagram0".equals(diagram.getName())) {
            	assertFalse(diagram instanceof IActivityDiagram);
                return (IDataFlowDiagram)diagram;
            }
        }
        fail("no diagram");
        return null;
    }

}

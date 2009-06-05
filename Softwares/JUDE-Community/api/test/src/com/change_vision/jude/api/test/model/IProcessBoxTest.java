package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IDataFlowDiagram;
import com.change_vision.jude.api.inf.model.IDataFlowNode;
import com.change_vision.jude.api.inf.model.IDiagram;
import com.change_vision.jude.api.inf.model.IProcessBox;

public class IProcessBoxTest extends ITestCase {
    
	public static Test suite() {
        return suite("testModel/judeAPITest/IDataFlowDiagramTest.jude", IProcessBoxTest.class);
    }
	
	public void testDataFlowNodes() {
    	IDataFlowDiagram dgm = getDiagram();
    	IDataFlowNode[] dfns = dgm.getDataFlowNodes();
    	assertEquals(dfns.length, 7);
    	
    	IProcessBox targetProcess = null;
    	for(int i = 0; i < dfns.length; i++) {
    		if (dfns[i] instanceof IProcessBox && dfns[i].getName().equals("ProcessBox0")) {
    			 targetProcess = (IProcessBox)dfns[i];
    		}
    	}	
    	assertNotNull(targetProcess);
    	assertEquals(targetProcess.getProcessBoxID(), "processBox0-id");
    	assertEquals(targetProcess.getOperator(), "processBox0-operator");
    	assertEquals(targetProcess.getDataFlowDiagram().getName(), "ProcessBox0");
    	assertEquals(targetProcess.getIncomings().length, 3);
    	assertEquals(targetProcess.getOutgoings().length, 3);
    }
    
    private IDataFlowDiagram getDiagram() {
        IDiagram[] dgms = project.getDiagrams();
        for (int i = 0; i < dgms.length; i++) {
            IDiagram diagram = dgms[i];
            if ("Data Flow Diagram0".equals(diagram.getName())) {
                return (IDataFlowDiagram)diagram;
            }
        }
        fail("no diagram");
        return null;
    }
}



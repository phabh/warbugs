package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IComment;
import com.change_vision.jude.api.inf.model.IDiagram;

public class IDiagramTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IActivityDiagramTest.jude", IDiagramTest.class);
    }

    public void testGetTexts() {
        IDiagram[] dgms = project.getDiagrams();
        for (int i = 0; i < dgms.length; i++) {
            IDiagram diagram = dgms[i];
            if ("ActivityDiagram0".equals(diagram.getName())) {
                String[] texts = diagram.getText();
                assertEquals("text1", texts[0]);
                assertEquals("text2", texts[1]);
                assertEquals("text3", texts[2]);
                break;
            }
        }
    }
    
    public void testGetComments() {
        IDiagram[] dgms = project.getDiagrams();
        for (int i = 0; i < dgms.length; i++) {
            IDiagram diagram = dgms[i];
            if ("ActivityDiagram0".equals(diagram.getName())) {
            	IComment[] comments = diagram.getComments();
            	assertTrue(comments.length == 2);
                assertEquals("Comment1", comments[0].getBody());
                assertEquals("Comment2", comments[1].getBody());
                break;
            }
        }
    }
}

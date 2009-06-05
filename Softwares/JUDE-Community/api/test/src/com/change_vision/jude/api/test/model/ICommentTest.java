package com.change_vision.jude.api.test.model;

import com.change_vision.jude.api.inf.model.IComment;
import com.change_vision.jude.api.inf.model.IElement;
import junit.framework.Test;

public class ICommentTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IElementTest.jude", ICommentTest.class);
    }

    public void testGetBody() {
        IElement element = getElement(project.getOwnedElements(), "Class0");
        IComment[] comments = element.getComments();
        assertEquals("comment1", comments[0].getBody());
        assertEquals("comment2\nL1\nL2", comments[1].getBody());
	}

	public void testAnnoteatedElements() {
        IElement element = getElement(project.getOwnedElements(), "Class0");
        IComment[] comments = element.getComments();
        assertEquals(2, comments[0].getAnnotatedElements().length);
        assertEquals(project, comments[0].getAnnotatedElements()[0]);
        assertEquals(element, comments[0].getAnnotatedElements()[1]);
        assertEquals(2, comments[1].getAnnotatedElements().length);
        assertEquals(project, comments[1].getAnnotatedElements()[0]);
        assertEquals(element, comments[1].getAnnotatedElements()[1]);
    }
}

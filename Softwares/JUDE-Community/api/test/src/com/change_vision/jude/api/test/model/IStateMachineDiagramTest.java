package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IFinalState;
import com.change_vision.jude.api.inf.model.IPseudostate;
import com.change_vision.jude.api.inf.model.IState;
import com.change_vision.jude.api.inf.model.IStateMachine;
import com.change_vision.jude.api.inf.model.IStateMachineDiagram;
import com.change_vision.jude.api.inf.model.ITransition;
import com.change_vision.jude.api.inf.model.IVertex;

public class IStateMachineDiagramTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IStateMachineDiagramTest.jude", IStateMachineDiagramTest.class);
    }
    
    public void testGetDiagram() {
    	IStateMachineDiagram dgm = (IStateMachineDiagram)getElement(project.getDiagrams(), "StateMachineDiagram0");
        assertNotNull(dgm);
        
        IStateMachine sm = dgm.getStateMachine();
        assertNotNull(sm);
        
        IVertex[] vs = sm.getVertexes();
		if (vs.length != 12) {
			fail();
		}
        ITransition[] ts = sm.getTransitions();
		if (ts.length != 14) {
			fail();
		}
		
		//InitialState
		IPseudostate inital = getInitialState(sm);
		
		//Transition
		ITransition[] t1s = inital.getOutgoings();
		if (t1s.length != 1) {
			fail();
		}
		if (!t1s[0].getGuard().equals("g1")) {
			fail();
		}
		if (!t1s[0].getAction().equals("a1")) {
			fail();
		}
		IVertex inital2 = t1s[0].getSource();
		if (!inital.equals(inital2)) {
			fail();
		}
		
		//State
		IState state0 = (IState)t1s[0].getTarget();
		if (!state0.getName().equals("State0")) {
			fail();
		}
		if (!state0.getEntry().equals("a_entry")) {
			fail();
		}
		if (!state0.getDoActivity().equals("a_do")) {
			fail();
		}
		if (!state0.getExit().equals("a_exit")) {
			fail();
		}
		
		//State
		IVertex[] svs = state0.getSubvertexes();
		if (svs.length != 1) {
			fail();
		}
		if (!svs[0].getName().equals("State4")) {
			fail();
		}
		
		//InternalTransition
		ITransition[] its = state0.getInternalTransitions();
		if (its.length != 2) {
			fail();
		}
		if (!its[0].getEvent().equals("event1")) {
			fail();
		}
		if (!its[0].getGuard().equals("guard1")) {
			fail();
		}
		if (!its[0].getAction().equals("action1")) {
			fail();
		}
		
		//Transition
		ITransition[] t2s = state0.getOutgoings();//ì‡ïîëJà⁄Çä‹Ç›Ç‹Ç∑.
		if (t2s.length != 3) {
			fail();
		}
		//ì‡ïîëJà⁄ÇéÊÇËèúÇ≠.
		ITransition t2 = getNonInternalTransition(its, t2s);
		if (!t2.getEvent().equals("e2")) {
			fail();
		}
		if (!t2.getGuard().equals("g2")) {
			fail();
		}
		if (!t2.getAction().equals("a2")) {
			fail();
		}
		
		//ShallowHistoryPseudostate
		IPseudostate shallowHis = (IPseudostate)t2.getTarget();
		if (!shallowHis.isShallowHistoryPseudostate()) {
			fail();
		}

		//Transition
		ITransition[] t3s = shallowHis.getOutgoings();
		if (t3s.length != 1) {
			fail();
		}
		
		//JunctionPseudostate
		IPseudostate junctionPseudostate = (IPseudostate)t3s[0].getTarget();
		if (!junctionPseudostate.isJunctionPseudostate()) {
			fail();
		}
		
		//Transition
		ITransition[] t4s = junctionPseudostate.getOutgoings();
		if (t4s.length != 1) {
			fail();
		}
		
		//choicePseudostate
		IPseudostate choicePseudostate = (IPseudostate)t4s[0].getTarget();
		if (!choicePseudostate.isChoicePseudostate()) {
			fail();
		}
		
		//Transition
		ITransition[] t5s = choicePseudostate.getOutgoings();
		if (t5s.length != 1) {
			fail();
		}
		
		//ForkPseudostate
		IPseudostate forkPseudostate = (IPseudostate)t5s[0].getTarget();
		if (!forkPseudostate.isForkPseudostate()) {
			fail();
		}
		
		//Transition
		ITransition[] t6s = forkPseudostate.getOutgoings();
		if (t6s.length != 2) {
			fail();
		}
		
		//State
		IState state2 = (IState)t6s[0].getTarget();
		if (!state2.getName().equals("State2")) {
			fail();
		}
		
		//Transition
		ITransition[] t7s = state2.getOutgoings();
		if (t7s.length != 1) {
			fail();
		}
		
		//Fork
		IPseudostate fork1 = (IPseudostate)t7s[0].getTarget();
		
		//State
		IState state1 = (IState)t6s[1].getTarget();
		if (!state1.getName().equals("State1")) {
			fail();
		}
		
		//Transition
		ITransition[] t8s = state1.getOutgoings();
		if (t8s.length != 1) {
			fail();
		}
		
		//Fork
		IPseudostate fork2 = (IPseudostate)t8s[0].getTarget();
		if (!fork1.equals(fork2)){ 
			fail();
		}
		
		//Transition
		ITransition[] t9s = fork1.getOutgoings();
		if (t9s.length != 1) {
			fail();
		}
		
		//subMachine
		IState subMachine = (IState)t9s[0].getTarget();
		if (!subMachine.getName().equals("SubmachineState0")) {
			fail();
		}
		if (!subMachine.isSubmachineState()) {
			fail();
		}
		if (!subMachine.getEntry().equals("sub_a_entry")) {
			fail();
		}
		if (!subMachine.getDoActivity().equals("sub_a_do")) {
			fail();
		}
		if (!subMachine.getExit().equals("sub_a_exit")) {
			fail();
		}
		IStateMachine sm2 =  subMachine.getSubmachine();
		assertNotNull(sm2);
		IStateMachineDiagram sm2dgm = sm2.getStateMachineDiagram();
		assertNotNull(sm2dgm);
		if (!sm2dgm.getName().equals("StateMachineDiagram1")) {
			fail();
		}
		
		//UStubState
		IVertex[] svs2 = subMachine.getSubvertexes();
		if (svs2.length != 2) {
			fail();
		}
		if (!svs2[0].getName().equals("StubState0")) {
			fail();
		}
		if (!svs2[1].getName().equals("StubState1")) {
			fail();
		}
		
		//Transition
		ITransition[] t10s = svs2[0].getOutgoings();
		if (t10s.length != 1) {
			fail();
		}
		
		//State
		IState state3 = (IState)t10s[0].getTarget();
		if (!state3.getName().equals("State3")) {
			fail();
		}
		
		//Transition
		ITransition[] t11s = state3.getOutgoings();
		if (t11s.length != 1) {
			fail();
		}

		//UStubState
		IPseudostate stub = (IPseudostate)t11s[0].getTarget();
		if (!stub.getName().equals("StubState1")) {
			fail();
		}
		if (!stub.equals(svs2[1])) {
			fail();
		}
		
		//Transition
		ITransition[] t12s = stub.getOutgoings();
		if (t12s.length != 1) {
			fail();
		}
		
		//finalState
		IVertex finalState1 = (IVertex)t12s[0].getTarget();
		if ( finalState1 instanceof IFinalState == false) {
			fail();
		}
		
		//Transition
		ITransition[] t13s = subMachine.getOutgoings();
		if (t13s.length != 1) {
			fail();
		}
		
		//finalState
		IFinalState finalState2 = (IFinalState)t13s[0].getTarget();
		if (!finalState2.equals(finalState1)) {
			fail();
		}
    }
    
    private IPseudostate getInitialState(IStateMachine sm){
    	IVertex[] vs = sm.getVertexes();
    	for (int i = 0; i < vs.length; i++) {
    		if (vs[i] instanceof IPseudostate) {
    			if (((IPseudostate)vs[i]).isInitialPseudostate()) {
    				return (IPseudostate)vs[i];
    			}
    		}
    	}
    	return null;
    }
    
    private ITransition getNonInternalTransition(ITransition[] ts1, ITransition[] ts2){
    	for (int i = 0; i < ts2.length; i++) {
    		boolean isFind = false;
    		for (int j = 0; j < ts1.length; j++) {
    			if (ts2[i].equals(ts1[j])){
    				isFind = true;
    				break;
    			}
    		}
    		if (!isFind){
    			return ts2[i];
    		}
    	}
    	return null;
    }
}

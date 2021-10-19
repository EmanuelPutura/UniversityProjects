package Testing.ModelTesting;

import Model.DataStructures.*;
import Model.Exceptions.DictionaryException;
import Model.Exceptions.InvalidIndexException;
import Model.Exceptions.ListException;
import Model.Exceptions.StackException;
import org.junit.Assert;

public class ModelTesting {
    public static void test() {
        DataStructuresTesting.test();
        System.out.println("...testing model package");
    }
}

class DataStructuresTesting {
    public static void test() {
        testADTList();
        testADTStack();
        testADTDictionary();
    }

    public static void testADTList() {
        IADTList<String> list = new ADTList<String>();
        String[] strings = {"Michael", "Andrew", "Emmanuel", "Andree", "Lionel", "Barack"};

        for (String str : strings)
            list.add(str);

        Assert.assertEquals(list.size(), 6);
        Assert.assertFalse(list.isEmpty());

        for (int i = 0; i < list.size(); ++i) {
            try {
                Assert.assertEquals(strings[i], list.get(i));
            } catch (ListException | InvalidIndexException e) {
                Assert.fail();
            }
        }

        try {
            list.set(0, "Other");
        } catch (ListException | InvalidIndexException e) {
            Assert.fail();
        }
        try {
            Assert.assertEquals(list.get(0), "Other");
        } catch (ListException | InvalidIndexException e) {
            Assert.fail();
        }

        try {
            String name = list.get(list.size());
            Assert.fail();
        } catch (ListException | InvalidIndexException e) {
            Assert.assertTrue(true);
        }
    }

    public static void testADTStack() {
        IADTStack<Integer> stack = new ADTStack<Integer>();

        try {
            stack.pop();
            Assert.fail();
        } catch (StackException e) {
            Assert.assertEquals(e.getMessage(), "Cannot pop from an empty stack!");
        }

        try {
            stack.top();
            Assert.fail();
        } catch (StackException e) {
            Assert.assertEquals(e.getMessage(), "Cannot extract the top from an empty stack!");
        }

        Assert.assertTrue(stack.empty());
        stack.push(2);
        Assert.assertFalse(stack.empty());
        stack.push(3);

        try {
            Assert.assertEquals(3, (int) stack.pop());
        } catch (StackException e) {
            Assert.fail();
        }

        try {
            Assert.assertEquals(2, (int) stack.top());
        } catch (StackException e) {
            Assert.fail();
        }

        try {
            Assert.assertEquals(2, (int) stack.pop());
        } catch (StackException e) {
            Assert.fail();
        }

        Assert.assertTrue(stack.empty());
    }

    public static void testADTDictionary() {
        IADTDictionary<String, Integer> grades = new ADTDictionary<String, Integer>();

        try {
            grades.put("Michael", 9);
            grades.put("Marry", 10);
            grades.put("Daniel", 6);
            grades.put("Marie", 9);
            grades.put("Anthony", 8);
        } catch (DictionaryException e) {
            Assert.fail();
        }

        try {
            Assert.assertEquals((int) grades.search("Daniel"), 6);
            Assert.assertEquals((int) grades.search("Marry"), 10);
            Assert.assertNull(grades.search("Nobody"));
            Assert.assertEquals((int) grades.remove("Anthony"), 8);
            Assert.assertNull(grades.search("Anthony"));
        } catch (DictionaryException e) {
            Assert.fail();
        }
    }
}